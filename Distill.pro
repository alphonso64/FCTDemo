#-------------------------------------------------
#
# Project created by QtCreator 2016-11-29T16:01:30
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Distill
TEMPLATE = app

QMAKE_LFLAGS_WINDOWS = /SUBSYSTEM:WINDOWS,5.01

SOURCES += main.cpp\
        mainwindow.cpp \
    CusRect.cpp \
    imageproc.cpp \
    paintlabel.cpp \
    tcprwworker.cpp \
    cuscamera.cpp \
    cuslabel.cpp \
    algorithm/m_meanStdDev.cpp \
    algorithm/pic.cpp \
    algorithm/m_crossCorr.cpp \
    algorithm/match_util.cpp \
    algorithm/m_mulspectrums.cpp \
    algorithm/m_interal.cpp \
    algorithm/CNN.cpp \
    algorithm/Layer.cpp \
    algorithm/CNN_util.cpp \
    algorithm/m_matchtemp.cpp \
    algorithm/m_dft.cpp \
    algorithm/m_point.cpp \
    algorithm/m_size.cpp

HEADERS  += mainwindow.h \
    CusRect.h \
    imageproc.h \
    paintlabel.h \
    tcprwworker.h \
    DxImageProc.h \
    GxIAPI.h \
    cuscamera.h \
    cuslabel.h \
    algorithm/pic.h \
    algorithm/CNN_util.h \
    algorithm/CNN.h \
    algorithm/Layer.h \
    algorithm/match_util.h \
    algorithm/m_matchtemp.h \
    algorithm/m_interal.h \
    algorithm/m_meanStdDev.h \
    algorithm/m_crossCorr.h \
    algorithm/m_mulspectrums.h \
    algorithm/m_dft.h \
    algorithm/scalar.h \
    algorithm/m_point.h \
    algorithm/m_size.h \
    algorithm/m_parameter.h \
    algorithm/m_Complex.h \
    algorithm/m_autobuffer.h

FORMS    += mainwindow.ui

LIBS+=D:/lib/x86/GxIAPI.lib
LIBS+=D:/lib/x86/DxImageProc.lib
