#-------------------------------------------------
#
# Project created by QtCreator 2015-02-16T13:11:01
#
#-------------------------------------------------

CONFIG(debug, debug|release) {
    TARGET = QHGuid
} else : CONFIG(release, debug|release) {
    TARGET = QHGui
}

TEMPLATE = lib
CONFIG += staticlib
DESTDIR = ../lib
INCLUDEPATH += $$(BOOST_DIR)

DEFINES += QHGUI_LIBRARY

SOURCES += ../QHGui/qhGui.cpp \
    ../QHGui/HelpObject_.cpp \
    ../QHGui/CornerPromptBox.cpp \
    ../QHGui/Dialog.cpp \
    ../QHGui/EditedListWidget.cpp \
    ../QHGui/SelectListItemDlg.cpp \
    ../QHGui/StateSettingStackWgt.cpp \
    ../QHGui/SystemTrayIcon.cpp \
    ../QHGui/mulfiledialog.cpp

HEADERS += ../QHGui/qhGui.h \
    ../QHGui/HelpObject.h \
    ../QHGui/CornerPromptBox.h \
    ../QHGui/Dialog.h \
    ../QHGui/EditedListWidget.h \
    ../QHGui/SelectListItemDlg.h \
    ../QHGui/StateSettingStackWgt.h \
    ../QHGui/SystemTrayIcon.h \
    ../QHGui/mulfiledialog.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    ../QHGui/EditedListWidget.ui \
    ../QHGui/mulfiledialog.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../QHTool/lib/ -lQHTool
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../QHTool/lib/ -lQHToold
else:unix: LIBS += -L$$PWD/../../QHTool/lib/ -lQHTool

INCLUDEPATH += $$PWD/../../QHTool
DEPENDPATH += $$PWD/../../QHTool

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../QHTool/lib/libQHTool.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../QHTool/lib/libQHToold.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../QHTool/lib/QHTool.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../QHTool/lib/QHToold.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../QHTool/lib/libQHTool.a
