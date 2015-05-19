#-------------------------------------------------
#
# Project created by QtCreator 2015-01-07T09:50:07
#
#-------------------------------------------------

QT       -= gui
CONFIG(release, release|debug){
    TARGET = LearnStaticLibSub
} else: CONFIG(debug, release|debug){
    TARGET = LearnStaticLibSubd
}

TEMPLATE = lib
CONFIG += staticlib

SOURCES += LearnStaticLibSub.cpp

HEADERS += LearnStaticLibSub.h

DESTDIR = $${PWD}/../lib

unix {
    target.path = /usr/lib
    INSTALLS += target
}
