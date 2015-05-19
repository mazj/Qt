#-------------------------------------------------
#
# Project created by QtCreator 2014-05-26T15:12:32
#
#-------------------------------------------------

QT       -= gui
# windows 下，debug的静态库比release的静态库要多生成一pdb文件
CONFIG(release, release|debug) {
    TARGET = LearnStaticLib
} else : CONFIG(debug, release|debug) {
    TARGET = LearnStaticLibd
}

TEMPLATE = lib #库要指定 lib配置，默认是动态库
CONFIG += staticlib #静态库必须显式说明

SOURCES += LearnStaticLib.cpp

HEADERS += LearnStaticLib.h

INCLUDEPATH += $${PWD}/LearnStaticLibSub

DESTDIR = $${PWD}/lib

unix {
    target.path = /usr/lib
    INSTALLS += target
}
