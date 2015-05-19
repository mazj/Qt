#-------------------------------------------------
#
# Project created by QtCreator 2014-09-09T15:03:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HealthMan
TEMPLATE = app
DESTDIR = $$PWD/bin


SOURCES += src/main.cpp\
        src/HealthManMainWnd.cpp \
    src/RemindUI.cpp

HEADERS  += src/HealthManMainWnd.h \
    src/inc.h \
    src/RemindUI.h

FORMS    += src/HealthManMainWnd.ui \
    src/RemindUI.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../QHTool/lib/ -lQHTool
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../QHTool/lib/ -lQHToold
else:unix: LIBS += -L$$PWD/../../QHTool/lib/ -lQHTool

INCLUDEPATH += $$PWD/../../QHTool
DEPENDPATH += $$PWD/../../QHTool

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../QHTool/lib/QHTool.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../QHTool/lib/QHToold.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../QHTool/lib/libQHTool.a

RESOURCES += \
    HealthMan.qrc

RC_FILE = picture/healthMan.rc
