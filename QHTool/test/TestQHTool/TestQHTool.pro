#-------------------------------------------------
#
# Project created by QtCreator 2014-10-17T09:21:13
#
#-------------------------------------------------

QT       += xml testlib

greaterThan(QT_MAJOR_VERSION, 4) {
    QT       += widgets
}

TARGET = tst_QHToolTest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_QHToolTest.cpp \
    QHToolTest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    QHToolTest.h

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../lib/ -lQHTool
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../lib/ -lQHToold
else:mac: LIBS += -F$$PWD/../../lib/ -framework QHTool
else:unix: LIBS += -L$$PWD/../../lib/ -lQHTool

INCLUDEPATH += $$PWD/../../
DEPENDPATH += $$PWD/../../
