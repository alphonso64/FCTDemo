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
    imageproc.cpp

HEADERS  += mainwindow.h \
    CusRect.h \
    CusViewFinder.h \
    imageproc.h

FORMS    += mainwindow.ui
