#include <GL/glu.h>
#include <QtCore>
#include <QFileDialog>
#include "GLWidget.h"

//#define GRAY_COLOR
#define Y_COLOR

void GLWidget::read_bindata()
{
    QFile f(QFileDialog::getOpenFileName(this, "開啟建模檔", QString(), "binary (*.bindata)"));
    if (!f.open(QIODevice::ReadOnly))
        qDebug() << "Failed to read file!\n";

    util_pixel_cross_platform_storage px;
    while(f.read((char *)&px, sizeof(util_pixel_cross_platform_storage)) != -1 && !f.atEnd())
    {
        px.x -= 484; px.y = -(px.y - 246); px.z = px.z * -2 + 400;
        // this do implicit cast from util_pixel_cross_platform_storage to util_cast
        dqPx.push_back(px);
    }
    f.close();
}

GLWidget::GLWidget(QWidget * parent) : QGLWidget(parent), dqRotate(), dqPx(), lastPosX(), lastPosY()
{
    setMinimumSize(100, 50);
    resize(640, 480);
    setWindowTitle(QString("OCT 3維影像重建"));

    // read the binary file to dqPx
    read_bindata();
}

GLWidget::~GLWidget()
{
    for (rotation * it : dqRotate)
        delete it;
}

void GLWidget::initializeGL()
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glClearColor(0.1f, 0.44f, 0.6f, 1.0f);
    glClearDepth(1.0f);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(1400.0f, 0.0f, 0.0f,
              0.0f, 0.0f, 0.0f,
              0.0f, 1.0f, 0.0f);
}

void GLWidget::paintGL()
{
    // draw the model
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPopMatrix();
    glPushMatrix();

    // rotation order correction
    for (std::deque<rotation *>::reverse_iterator rit = dqRotate.rbegin(); rit != dqRotate.rend(); ++rit)
        (*rit)->rotate();

    glBegin(GL_POINTS);
        for(util_pixel px : dqPx)
        {
            // decide color by y value.
#ifdef Y_COLOR
            GLfloat colorA = (px.y + 246.0f) / 492.0f;
            GLfloat colorB = 1.0f - colorA;
#elif defined GRAY_COLOR
            const GLfloat refVal = 0.53f;
            GLfloat colorR = px.r >= refVal? (px.r - refVal) / (1.0f - refVal): 0.0f;
            GLfloat colorG;
            // (1 - refVal)/2 + refVal
            if (px.r > 0.3f * (1.0f + refVal))
                colorG = 0.0f;
            else if (px.r < refVal * 0.3f)
                colorG = 0.0f;
            else if (px.r >= refVal)
                // * 2.0f because the * 0.5 above
                colorG = 1.0f - (px.r - refVal) / (1.0f - refVal) / 0.3f;
            else
                colorG = 1.0f - (refVal - px.r) / refVal / 0.3f;

            GLfloat colorB = px.r < refVal? (refVal - px.r) / refVal: 0.0f;

#endif

            // And apply gray value as color saturation
#ifdef Y_COLOR
            glColor3f(colorA * px.r, colorB * px.g, colorA * px.b);
#elif defined GRAY_COLOR
            glColor3f(colorR, colorG, colorB);
#else
            glColor3f(px.r, px.g, px.b);
#endif
            glVertex3i(px.x, px.y, px.z);
        }
    glEnd(); // GL_POINTS

    // draw axis
    glBegin(GL_LINES);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3i(0, 0, 0);
        glVertex3i(1000, 0, 0);

        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3i(0, 0, 0);
        glVertex3i(0, 1000, 0);

        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3i(0, 0, 0);
        glVertex3i(0, 0, 1000);
    glEnd();    // GL_LINES

    // draw background
    glBegin(GL_QUADS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3i(-500, -300, 500);
        glVertex3i(-500, -300, -500);
        glVertex3i(500, -300, -500);
        glVertex3i(500, -300, 500);
    glEnd();    //GL_QUADS

    // QGLWidget will swap buffer automatically after painGL event
}

void GLWidget::resizeGL(int w, int h)
{

    glViewport(0, 0, w, h);
    GLdouble aspect = (GLdouble)w / (GLdouble)h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (aspect >= 1.0)
        glFrustum(-484.0 * aspect, 484.0 * aspect, -246.0, 246.0, 1000, 1900);
    else
        glFrustum(-484, 484, -246.0 / aspect, 246.0 / aspect, 1000, 1900);

    glMatrixMode(GL_MODELVIEW);
}

void GLWidget::mousePressEvent(QMouseEvent * ev)
{
    if (ev->modifiers() == Qt::NoModifier && ev->button() == Qt::LeftButton)
    {
        ev->accept();
        lastPosX = ev->x(); lastPosY = ev->y();
    }
    QGLWidget::mousePressEvent(ev);
}
void GLWidget::mouseMoveEvent(QMouseEvent * ev)
{
    int x; int y;
    bool shouldAccept = false;
    if (ev->modifiers() == Qt::NoModifier && ev->buttons() & Qt::LeftButton)
    {
        x = ev->x(); y = ev->y();
        if (abs(x - lastPosX) > 30)
        {
            dqRotate.push_front(new rotation_horizontal(x > lastPosX? 15.0f: -15.0f));
            lastPosX = x;
            shouldAccept = true;
        }
        if (abs(y - lastPosY) > 30)
        {
            dqRotate.push_back(new rotation_vertical(y > lastPosY? 15.0f: -15.0f));
            lastPosY = y;
            shouldAccept = true;
        }
    }

    if (shouldAccept)
    {
        ev->accept();
        glDraw();
    }

    QGLWidget::mouseMoveEvent(ev);
}

void GLWidget::keyPressEvent(QKeyEvent * ev)
{
    // ev->ignore() propagate to parent
    // but still require to manually call base class's event handler

    if (ev->modifiers() == Qt::NoModifier && (ev->key() == Qt::Key_Return || ev->key() == Qt::Key_Enter))
    {
        this->close();
    }
    else if (ev->modifiers() == Qt::NoModifier && ev->key() == Qt::Key_R)
    {
        for (rotation * it : dqRotate)
            delete it;

        dqRotate.clear();
        glDraw();
    }
    else
    {
        ev->ignore();
        QGLWidget::keyPressEvent(ev);
        return;
    }

    ev->accept();
}
