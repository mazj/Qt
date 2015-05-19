#-------------------------------------------------
#
# Project created by QtCreator 2014-05-26T15:28:15
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = LinkLib
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp

# ���ӵ���̬�� LearnSharedLib
#1
win32:CONFIG(release, debug|release) {
# ������д�����е�
#    LIBS += -L$$PWD/../LearnSharedLib/lib/ -lLearnSharedLib
    LIBS += $$PWD/../LearnSharedLib/lib/LearnSharedLib.lib
} else:win32:CONFIG(debug, debug|release) {
    LIBS += -L$$PWD/../LearnSharedLib/lib/ -lLearnSharedLibd
} else:unix {
    LIBS += -L$$PWD/../LearnSharedLib/lib/ -lLearnSharedLib
}

INCLUDEPATH += $$PWD/../LearnSharedLib
DEPENDPATH += $$PWD/../LearnSharedLib


# ���ӵ���̬�� LearnStaticLib  windows �� ���ӵ� ��̬�� �� ��̬���д����һ����
#2
win32:CONFIG(release, debug|release) {
# ������д�����е�
#    LIBS += -L$$PWD/../LearnStaticLib/lib/ -lLearnStaticLib
    LIBS += $$PWD/../LearnStaticLib/lib/LearnStaticLib.lib
    LIBS += -L$$PWD/../LearnStaticLib/lib -lLearnStaticLibSub
} else:win32:CONFIG(debug, debug|release) {
    LIBS += -L$$PWD/../LearnStaticLib/lib/ -lLearnStaticLibd
    LIBS += -L$$PWD/../LearnStaticLib/lib -lLearnStaticLibSubd
} else:mac {
    LIBS += -F$$PWD/../LearnStaticLib/lib/ -framework LearnStaticLib
} else:unix {
    LIBS += -L$$PWD/../LearnStaticLib/lib/ -lLearnStaticLib
}

INCLUDEPATH += $$PWD/../LearnStaticLib
DEPENDPATH += $$PWD/../LearnStaticLib
#2
