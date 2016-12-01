#-------------------------------------------------
#
# Project created by QtCreator 2016-11-29T16:01:30
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia
QT       += multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Distill
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    CusRect.cpp \
    CusViewFinder.cpp \
    imageproc.cpp \
    CNN.cpp \
    Layer.cpp \
    util.cpp \
    util_liang.cpp \
    paintlabel.cpp

HEADERS  += mainwindow.h \
    CusRect.h \
    CusViewFinder.h \
    imageproc.h \
    CNN.h \
    Layer.h \
    util.h \
    util_liang.h \
    paintlabel.h

FORMS    += mainwindow.ui

INCLUDEPATH+=C:/opencv/build/include/opencv \
                    C:/opencv/build/include/opencv2 \
                   C:/opencv/build/include
LIBS+=C:/opencv/build/x64/vc12/lib/opencv_world310d.lib
