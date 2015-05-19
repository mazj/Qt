#-------------------------------------------------
#
# Project created by QtCreator 2014-06-18T15:47:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DebugMsgExample
TEMPLATE = app


SOURCES += main.cpp\
        DebugMsgMainWnd.cpp

HEADERS  += DebugMsgMainWnd.h

FORMS    += DebugMsgMainWnd.ui

INCLUDEPATH += $$(QHTOOL_ROOT)
DEPENDPATH += $$(QHTOOL_ROOT)

win32:CONFIG(release, debug|release): LIBS += -L$$(QHTOOL_ROOT)/lib -lQHTool
else:win32:CONFIG(debug, debug|release): LIBS += -L$$(QHTOOL_ROOT)/lib -lQHToold
else:unix: LIBS += -L$$(QHTOOL_ROOT)/lib -lQHTool


#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../lib/ -lQHTool
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../lib/ -lQHToold
#else:unix: LIBS += -L$$PWD/../../lib/ -lQHTool

#INCLUDEPATH += $$PWD/../../
#DEPENDPATH += $$PWD/../../
