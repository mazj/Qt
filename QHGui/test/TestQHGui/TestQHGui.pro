#-------------------------------------------------
#
# Project created by QtCreator 2015-02-16T13:31:30
#
#-------------------------------------------------

QT       += widgets testlib

TARGET = tst_testqhguitest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_testqhguitest.cpp \
    QHGuiTest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    QHGuiTest.h

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../lib/ -lQHGui
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../lib/ -lQHGuid
else:mac: LIBS += -F$$PWD/../../lib/ -framework QHTool
else:unix: LIBS += -L$$PWD/../../lib/ -lQHTool

INCLUDEPATH += $$PWD/../../
DEPENDPATH += $$PWD/../../
