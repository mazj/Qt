#-------------------------------------------------
#
# Project created by QtCreator 2017-03-25T17:52:54
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = testLocalCommunicator
TEMPLATE = app


SOURCES += main.cpp\
        communicatormainwindow.cpp \
    ../../QHTool/LocalCommunicator.cpp

HEADERS  += communicatormainwindow.h \
    ../../QHTool/LocalCommunicator.h

FORMS    += communicatormainwindow.ui
