#-------------------------------------------------
#
# Project created by QtCreator 2014-06-05T13:40:11
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QHGuiGeneralExample
TEMPLATE = app


SOURCES += main.cpp \
        GeneralMainWnd.cpp

HEADERS  += GeneralMainWnd.h

FORMS    += GeneralMainWnd.ui


# -lQHTool  -lQHToold
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../lib/ QHGui.lib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../lib/ QHGuid.lib
else:unix: LIBS += -L$$PWD/../../lib/ -lQHGui

INCLUDEPATH += $$PWD/../../
DEPENDPATH += $$PWD/../../

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../lib/QHGui.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../lib/QHGuid.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../lib/QHGui.a


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../QHTool/lib/ -lQHTool
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../QHTool/lib/ -lQHToold
else:unix: LIBS += -L$$PWD/../../../QHTool/lib/ -lQHTool

INCLUDEPATH += $$PWD/../../../QHTool
DEPENDPATH += $$PWD/../../../QHTool

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../QHTool/lib/libQHTool.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../QHTool/lib/libQHToold.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../QHTool/lib/QHTool.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../QHTool/lib/QHToold.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../../QHTool/lib/libQHTool.a


RESOURCES += \
    QHGuiGeneralExample.qrc
