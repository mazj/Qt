#-------------------------------------------------
#
# Project created by QtCreator 2014-05-27T11:41:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += widgets
}

TARGET = AppUsingPlugin
TEMPLATE = app
DESTDIR += ../bin

SOURCES += main.cpp\
        MainWidget.cpp

HEADERS  += MainWidget.h \
    ../MyPlugin/IMyPlugin.h

FORMS    += MainWidget.ui
