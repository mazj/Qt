#-------------------------------------------------
#
# Project created by QtCreator 2014-05-26T15:09:05
#
#-------------------------------------------------

QT       -= gui

# windows �£�debug�Ķ�̬���release�Ķ�̬��Ҫ������һЩ�ļ�
CONFIG(release, release|debug) {
    TARGET = LearnSharedLib
} else : CONFIG(debug, release|debug) {
    TARGET = LearnSharedLibd
}

TEMPLATE = lib #��Ҫָ�� lib���ã�Ĭ���Ƕ�̬��

DEFINES += LEARNSHAREDLIB_LIBRARY

SOURCES += LearnSharedLib.cpp

HEADERS += LearnSharedLib.h\
        learnsharedlib_global.h

DESTDIR = $${PWD}/lib

unix {
    target.path = /usr/lib
    INSTALLS += target
}
