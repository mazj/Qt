#-------------------------------------------------
#
# Project created by QtCreator 2015-02-16T13:12:41
#
#-------------------------------------------------

QT       += widgets

TARGET = QHGui
TEMPLATE = lib
CONFIG += staticlib

SOURCES += qhGui.cpp

HEADERS += qhGui.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
