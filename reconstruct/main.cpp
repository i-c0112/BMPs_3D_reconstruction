#define GLUT_DISABLE_ATEXIT_HACK
#include <cstdio>
#include <deque>
#include <utility>
#include <GL\freeglut.h>
#include "bitmap_image.hpp"
#include "struct_pixel.h"
#include "bmp2csv.h"

static std::deque<util_pixel> dqPx;

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
void read_bmps(int total)
{
    for (int idx = 1; idx <= total; ++idx)
    {
        read_single_bmp(idx);
    }
}
#else
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

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

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
            break;

        case 'a':
            glRotatef(-30.0, 0.0, 1.0, 0.0);
            glutPostRedisplay();
            break;
        case 'd':
            glRotatef(30.0, 0.0, 1.0, 0.0);
            glutPostRedisplay();
            break;
        case 'w':
            glRotatef(-30.0, 0.0, 0.0, -1.0);
            glutPostRedisplay();
            break;
        case 's':
            glRotatef(30.0, 0.0, 0.0, -1.0);
            glutPostRedisplay();
            break;

        default:
            fprintf(stderr, "What are you pressing now?\n");
            break;
    }
}

inline void init()
{
    glClearColor(0, 0, 0, 0);
    glEnable(GL_POINT_SMOOTH);

    glMatrixMode(GL_MODELVIEW);
//    gluLookAt(0.0, 0.0, 1400.0,
//              0.0, 0.0, 0.0,
//              0.0, 1.0, 0.0);
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
    #else
    read_pixels_from_csv();
    #endif // READ_BMP
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("BMPs");

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(key_stroke);

    read_pixel_data();

    glutMainLoop();
    glutExit();

    return 0;
}
