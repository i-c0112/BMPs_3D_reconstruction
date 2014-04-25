#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QWidget>
#include <QtOpenGL>
#include <deque>
#include "struct_pixel.h"
#include "struct_rotation.h"

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    explicit GLWidget(QWidget * parent = nullptr);
    ~GLWidget();

protected:
    // events related to GL context
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

    // Window event
    void mousePressEvent(QMouseEvent *);
    // this is not neccessary since mouseMoveEvent alreadt take care of which buttons are pressed
    //void mouseReleaseEvent(QMouseEvent *);

    void mouseMoveEvent(QMouseEvent *);
    void keyPressEvent(QKeyEvent *);

private:
    // stack for reverse rotations
    std::deque<rotation *> dqRotate;

    // container of the pixels
    std::deque<util_pixel> dqPx;

    // mouseMoveEvent
    int lastPosX;
    int lastPosY;

    void read_bindata();
};

#endif // GLWIDGET_H
