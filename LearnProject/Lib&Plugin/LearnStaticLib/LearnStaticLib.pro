#-------------------------------------------------
#
# Project created by QtCreator 2014-05-26T15:12:32
#
#-------------------------------------------------

QT       -= gui
# windows �£�debug�ľ�̬���release�ľ�̬��Ҫ������һpdb�ļ�
CONFIG(release, release|debug) {
    TARGET = LearnStaticLib
} else : CONFIG(debug, release|debug) {
    TARGET = LearnStaticLibd
}

TEMPLATE = lib #��Ҫָ�� lib���ã�Ĭ���Ƕ�̬��
CONFIG += staticlib #��̬�������ʽ˵��

SOURCES += LearnStaticLib.cpp

HEADERS += LearnStaticLib.h

INCLUDEPATH += $${PWD}/LearnStaticLibSub

DESTDIR = $${PWD}/lib

unix {
    target.path = /usr/lib
    INSTALLS += target
}
