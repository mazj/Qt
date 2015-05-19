#-------------------------------------------------
#
# Project created by QtCreator 2014-09-12T19:16:11
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TestQSettingsXmlFormat
TEMPLATE = app


SOURCES += main.cpp \
    TestQSettingMainWnd.cpp

HEADERS  += \
    TestQSettingMainWnd.h

FORMS    += MainWindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../lib/ -lQHTool
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../lib/ -lQHToold
else:unix: LIBS += -L$$PWD/../../lib/ -lQHTool

INCLUDEPATH += $$PWD/../../
DEPENDPATH += $$PWD/../../

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../lib/QHTool.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../lib/QHToold.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../lib/libQHTool.a
