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
# �����Ƹĳ� qhDebugMsg.cpp �򲻻ᱻ���룬����ԭ���� qmake���ɵ�Makefile ������
# qhDebugMsg.cpp �ļ���Ī���� qmake��bug��
# �ļ� HelpObject.cppҲ����������
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

