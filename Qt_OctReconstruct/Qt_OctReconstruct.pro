QT += core gui opengl
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = Qt_OctReconstruct
TEMPLATE = app

SOURCES += main.cpp \
    GLWidget.cpp

INCLUDEPATH += ../include

HEADERS += GLWidget.h struct_pixel.h \
    struct_rotation.h

DESTDIR = $$PWD/build
CONFIG += c++11
