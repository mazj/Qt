#-------------------------------------------------
#
# Project created by QtCreator 2015-03-01T17:29:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MarketManage
TEMPLATE = app


SOURCES += main.cpp\
        marketmainwnd.cpp \
    userpassworddlg.cpp \
    global.cpp \
    PersonnelManage.cpp \
    InGoods.cpp \
    SellGoods.cpp \
    profit.cpp \
    StockWidget.cpp \
    SysMaintainWidget.cpp

HEADERS  += marketmainwnd.h \
    userpassworddlg.h \
    global.h \
    PersonnelManage.h \
    InGoods.h \
    SellGoods.h \
    profit.h \
    StockWidget.h \
    SysMaintainWidget.h

FORMS    += marketmainwnd.ui \
    userpassworddlg.ui \
    PersonnelManage.ui \
    InGoods.ui \
    SellGoods.ui \
    profit.ui \
    StockWidget.ui \
    SysMaintainWidget.ui
