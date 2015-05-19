#-------------------------------------------------
#
# Project created by QtCreator 2014-06-09T15:09:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EditedListWidgetExample
TEMPLATE = app


SOURCES += main.cpp\
        EditedListMainWnd.cpp

HEADERS  += EditedListMainWnd.h

FORMS    += EditedListMainWnd.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../lib/ -lQHTool
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../lib/ -lQHToold
else:mac: LIBS += -F$$PWD/../../lib/ -framework QHTool
else:unix: LIBS += -L$$PWD/../../lib/ -lQHTool

INCLUDEPATH += $$PWD/../../
DEPENDPATH += $$PWD/../../
