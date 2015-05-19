#-------------------------------------------------
#
# Project created by QtCreator 2014-06-16T10:34:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UsingListWidget
TEMPLATE = app


SOURCES += main.cpp \
        ListwidgetMainWnd.cpp \
    MyListModel.cpp \
    ListWidget.cpp

HEADERS  += ListwidgetMainWnd.h \
    MyListModel.h \
    ListWidget.h

FORMS    += ListwidgetMainWnd.ui

INCLUDEPATH += $$(QHTOOL_ROOT)
DEPENDPATH += $$(QHTOOL_ROOT)

win32:CONFIG(release, debug|release): LIBS += -L$$(QHTOOL_ROOT)/lib/ -lQHTool
else:win32:CONFIG(debug, debug|release): LIBS += -L$$(QHTOOL_ROOT)/lib/ -lQHToold
else:unix: LIBS += -L$$(QHTOOL_ROOT)/lib/ -lQHTool

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$(QHTOOL_ROOT)/lib/QHTool.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$(QHTOOL_ROOT)/lib/QHToold.lib
else:unix: PRE_TARGETDEPS += $$(QHTOOL_ROOT)/lib/libQHTool.a
