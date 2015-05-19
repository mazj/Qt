#-------------------------------------------------
#
# Project created by QtCreator 2014-06-05T13:44:57
#
#-------------------------------------------------

greaterThan(QT_MAJOR_VERSION, 4) {
    QT       += widgets
}

QT += xml

CONFIG(debug, debug|release) {
    TARGET = QHToold
} else : CONFIG(release, debug|release) {
    TARGET = QHTool
}

TEMPLATE = lib
CONFIG += staticlib
DESTDIR = ../lib
INCLUDEPATH += $$(BOOST_DIR)

SOURCES += ../QHTool/QHTool.cpp \
    ../QHTool/qHelpFunction.cpp \
    ../QHTool/IniNote.cpp \
    ../QHTool/qhDebugMsg_.cpp \
    #XmlSettings.cpp
# 若名称改成 qhDebugMsg.cpp 则不会被编译，发现原因是 qmake生成的Makefile 不包含
# qhDebugMsg.cpp 文件，莫非是 qmake的bug？
# 文件 HelpObject.cpp也是类似现象
    ../QHTool/qhXml.cpp

HEADERS += ../QHTool/QHTool.h \
    ../QHTool/qHelpFunction.h \
    ../QHTool/IniNote.h \
    ../QHTool/qhDebugMsg.h \
    #XmlSettings.h
    ../QHTool/qhXml.h \
    ../QHTool/QHToolGlobal.h \
    ../QHTool/SettingTextCodec.hpp


unix {
    target.path = /usr/lib
    INSTALLS += target
}

