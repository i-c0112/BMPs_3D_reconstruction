#include <cstdio>
#include <deque>
#include <utility>
#include <GL\freeglut.h>
#include "bitmap_image.hpp"
#include "struct_pixel.h"

//! storage of pixels(should be optimized to successive memory storage)
static std::deque<util_pixel> dqPx;
//! forward declaration required by dqRotate
struct rotation;
//! tweak to do right rotate order of glRotate
static std::deque<rotation*> dqRotate;
//! variable used in mouse event
bool isButtonDown = false;
static int origX, origY;

//! priority: READ_BMP > READ_BIN > READ_CSV
//! defaut: READ_CSV
#define READ_BIN
#ifdef READ_BMP
void read_single_bmp(int idx)
{
    char filename_to_read[16];
    sprintf(filename_to_read, "Sample/%i.bmp", idx);

    bitmap_image bmp(filename_to_read);

    unsigned int h = bmp.height();
    unsigned int w = bmp.width();

    /// !!!!!!!!!!!!!!!!WEIRD!!!!!!!!!!!
    /// height need to minus 2 or there will be white lines at the bottom of the pic!
    for (unsigned int y = 0; y < h-2; ++y)
    {
        for (unsigned int x = 0; x < w; ++x)
        {
            unsigned char uR, uG, uB;
            bmp.get_pixel(x, y, uR, uG, uB);

            if (uR < 128 && uG < 128 && uB < 128)
                continue;

            util_pixel px;
            px.x = x - 484; px.y = -(y - 246); px.z = idx * -2 + 400;
            px.r = rgb_b2f(uR); px.g = rgb_b2f(uG); px.b = rgb_b2f(uB);
            dqPx.push_back(px);
        }
    }
}
inline void read_bmps(int total)
{
    for (int idx = 1; idx <= total; ++idx)
    {
        read_single_bmp(idx);
    }
}
#elif defined READ_BIN
#include "bmp2binary.h"
void read_pixels_from_binary()
{
    std::fstream fd;
    if (!bmp2binary_open_for_read(fd))
    {
        fprintf(stderr, "Failed to open %s!\n", BIN_FILENAME);
        return;
    }
    util_pixel px;
    while (bmp2binary_read(fd, px))
    {
        px.x = px.x - 484; px.y = -(px.y - 246); px.z = px.z * -2 + 400;
        dqPx.push_back(px);
    }
}
#include "bmp2csv.h"
void read_pixels_from_csv()
{
    FILE *fd = nullptr;
    util_pixel px;
    /// feof after read operation:
    /// make sure last read operation which reached EOF will NOT go through the loop!
    while ( (fd = bmp2csv_read(&px, fd) ) && !feof(fd))
    {
        px.x = px.x - 484; px.y = -(px.y - 246); px.z = px.z * -2 + 400;
        dqPx.push_back(px);
    }
}
#endif

struct rotation
{
    virtual void rot() {};

    virtual ~rotation() {}
};
struct rotation_horizontal : rotation
{
    float deg;
    explicit rotation_horizontal(float arg_deg) : deg(arg_deg) {}
    virtual void rot()
    {
        glRotatef(deg, 0.0f, 1.0f, 0.0f);
    }

    virtual ~rotation_horizontal() {}
};
struct rotation_vertical : rotation
{
    float deg;
    explicit rotation_vertical(float arg_deg) : deg(arg_deg) {}
    virtual void rot()
    {
        glRotatef(deg, 0.0f, 0.0f, -1.0f);
    }

    virtual ~rotation_vertical() {}
};
inline void do_rotations()
{
    for (std::deque<rotation*>::reverse_iterator rit = dqRotate.rbegin(); rit != dqRotate.rend(); ++rit)
    {
        (*rit)->rot();
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glPopMatrix();
    glPushMatrix();
    do_rotations();

    glBegin(GL_POINTS);
        for (util_pixel px : dqPx)
        {
            glColor3f(px.r, px.g, px.b); glVertex3i(px.x, px.y, px.z);
        }
    glEnd();

    glutSwapBuffers();
}

void key_stroke(unsigned char key, int x, int y)
{
    switch (key)
    {
        case '\r':
            glutLeaveMainLoop();
            return;
        case 'a':
            dqRotate.push_back(new rotation_horizontal(30.0f));
            break;
        case 'd':
            dqRotate.push_back(new rotation_horizontal(-30.0f));
            break;
        case 'w':
            dqRotate.push_back(new rotation_vertical(30.0f));
            break;
        case 's':
            dqRotate.push_back(new rotation_vertical(-30.0f));
            break;

        default:
            fprintf(stderr, "What are you pressing now?\n");
            return;
    }
    glutPostRedisplay();
}

void mouse_clicked(int button, int state, int x, int y)
{
    /// this is called only when buttons clicked or released.
    /// so if you want to drag things you'll need MotionFunc
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            isButtonDown = true;

            /// rotate the modelview
            /// dont be too sensitive, so store the distance to check if rotation is required
            origX = x;
            origY = y;
        }
        else
            isButtonDown = false;
    }
}
void mouse_motion(int x, int y)
{
    if (!isButtonDown)
        return;

    bool shouldDraw = false;
    /// according to MilkShape3D: horizontal difference always account for rotate around y-axis
    if (abs(x - origX) > 30)
    {
//        glRotatef( x > origX? 15.0f: -15.0f , 0.0f, 1.0f, 0.0f);
        dqRotate.push_front(new rotation_horizontal(x > origX? -15.0f: 15.0f));
        origX = x;
        shouldDraw = true;
    }
    if (abs(y - origY) > 30)
    {
        dqRotate.push_back(new rotation_vertical(y > origY? 15.0f: -15.0f));
        origY = y;
        shouldDraw = true;
    }

    if (shouldDraw) glutPostRedisplay();
}

inline void init()
{
    glClearColor(0, 0, 0, 0);
    glEnable(GL_POINT_SMOOTH);

    glMatrixMode(GL_MODELVIEW);
    gluLookAt(-1400.0, 0.0, 0.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    glMatrixMode(GL_PROJECTION);
    glFrustum(-484.0, 484.0, -246.0, 246.0, 1000.0, 1900.0);

    glMatrixMode(GL_MODELVIEW);
}

inline void read_pixel_data()
{
    #ifdef READ_BMP
    read_bmps(400);
    #elif defined READ_BIN
    read_pixels_from_binary();
    #else
    read_pixels_from_csv();
    #endif // READ_BMP
}
void cleanup()
{
    for (auto it : dqRotate)
    {
        delete it;
    }
    dqRotate.clear();
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("BMPs");

    init();
    read_pixel_data();

    glutDisplayFunc(display);
    glutKeyboardFunc(key_stroke);
    glutMouseFunc(mouse_clicked);
    glutMotionFunc(mouse_motion);

    glutMainLoop();
    glutExit();

    cleanup();

    return 0;
}
