#-------------------------------------------------
#
# Project created by QtCreator 2014-06-10T13:51:35
#
#-------------------------------------------------

# Ŀǰ�����Ѿ��������� TestQHTool �У������Ŀ�ǾɵĲ��õ�

QT       += testlib xml

TARGET = tst_TestQHelpFunctionTest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_TestQHelpFunctionTest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../lib/ -lQHTool
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../lib/ -lQHToold
else:mac: LIBS += -F$$PWD/../../lib/ -framework QHTool
else:unix: LIBS += -L$$PWD/../../lib/ -lQHTool

INCLUDEPATH += $$PWD/../../
DEPENDPATH += $$PWD/../../
