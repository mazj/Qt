#-------------------------------------------------
#
# Project created by QtCreator 2014-05-27T10:58:01
#
#-------------------------------------------------

QT       -= gui

greaterThan(QT_MAJOR_VERSION, 4) {
    DEFINES += QT_5
    OTHER_FILES += MyPlugin.json
} else : equals(QT_MAJOR_VERSION, 4) {
    DEFINES += QT_4
} else {
    message("Cannot build this with Qt version $${QT_VERSION}.")
    error("Use at least Qt 4.0.0.")
}

TARGET = MyPlugin
TEMPLATE = lib
CONFIG += plugin #声明是插件

DEFINES += MYPLUGIN_LIBRARY #当插件使用时，好像可有可无。当普通动态库使用必须有
DESTDIR         = ../plugins

SOURCES += \
    MyPlugin.cpp

HEADERS +=\
        myplugin_global.h \
    IMyPlugin.h \
    MyPlugin.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

OTHER_FILES += \
    MyPlugin.json
