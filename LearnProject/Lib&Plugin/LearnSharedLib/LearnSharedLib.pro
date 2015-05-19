#-------------------------------------------------
#
# Project created by QtCreator 2014-05-26T15:09:05
#
#-------------------------------------------------

QT       -= gui

# windows 下，debug的动态库比release的动态库要多生成一些文件
CONFIG(release, release|debug) {
    TARGET = LearnSharedLib
} else : CONFIG(debug, release|debug) {
    TARGET = LearnSharedLibd
}

TEMPLATE = lib #库要指定 lib配置，默认是动态库

DEFINES += LEARNSHAREDLIB_LIBRARY

SOURCES += LearnSharedLib.cpp

HEADERS += LearnSharedLib.h\
        learnsharedlib_global.h

DESTDIR = $${PWD}/lib

unix {
    target.path = /usr/lib
    INSTALLS += target
}
