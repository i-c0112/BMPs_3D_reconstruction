#-------------------------------------------------
#
# Project created by QtCreator 2014-04-25T01:38:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qt_bmp2bin_gui
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    lineinputdialog.cpp \
    progressbardialog.cpp \
    threadbmpreadprogress.cpp

INCLUDEPATH += ../include

HEADERS  += mainwindow.h struct_pixel.h \
    lineinputdialog.h \
    progressbardialog.h \
    threadbmpreadprogress.h

FORMS    += mainwindow.ui \
    lineinputdialog.ui \
    progressbardialog.ui

DESTDIR = $$PWD/build
MOC_DIR = $$DESTDIR
OBJECTS_DIR = $$DESTDIT
RCC_DIR = $$DESTDIR

CONFIG += c++11
