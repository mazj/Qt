#-------------------------------------------------
#
# Project created by QtCreator 2014-05-22T16:29:06
#
#-------------------------------------------------

# 要用到的 qt模块
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# 生成的应用程序名称
TARGET = learnQmake
#编译应用程序类型
TEMPLATE = app


SOURCES += main.cpp\
        LearnQmakeMainWindow.cpp

HEADERS  += LearnQmakeMainWindow.h

FORMS    += LearnQmakeMainWindow.ui

# 我发现 在 windows qt5.2 中，在 CONFIG 中不指定 debug 和 release，会默认
# 同时添加 debug 和 release的，生成 三个 makefile， Makefile Makefile.debug
# Makefile.release
# 见 manual 的 qmake的 Variables部分：When you use the debug_and_release option (which is the default under Windows),


# 当 CONFIG 中 同时含有 debug 或 release选项时，只有有一个选项是当前激活的。这在 CONFIG中比较特殊
# 1这一块，只是判断 CONFIG 中 是否含有 debug 或 release选项，当前不管激活那个选项
#begin 1
debug {
    message(1 Debug build!)
}

release {
    message(1 release build!)
}

CONFIG(debug) {
    message(Debug build!)
}

CONFIG(release) {
    message(release build!)
}
#end 1

# 2 这块，要求含有 debug 或 release选项，又判断当前激活的是哪个选项
#begin 2
#第一个参数判断激活的选项， 第二个参数判断含有的选项
CONFIG(debug, debug|release) {
    message(2 Debug build!)
}

CONFIG(release, debug|release) {
    message(2 release build!)
}

#end 2

# install 安装部署信息，通过执行 make install 或 jom.exe install 执行
CONFIG(debug, debug|release) {
    target.path = $$PWD/debug_bin # 指定安装目录
} else:CONFIG(release, debug|release) {
    target.path = $$PWD/bin       # 引用qamke内置变量 PWD
# $$OUT_PWD makefile文件所在路径
# $$PWD   当前的pro文件所在路径
    message(target.path = bin!)
}

target.file = $$TARGET   # 指定安装文件
INSTALLS += target

#我们知道， qmake的最主要作用就是产生 makefile,而 makefile 的基本概念是
# 目标 依赖 命令，默认第一个目标是产生项目输出文件（可执行文件或者库），
# INSTALLS 变量指定的是 install 目标所依赖的目标，如果还要产生别的另外的目标
# 需要使用 QMAKE_EXTRA_TARGETS变量

mytarget.target = mytargetfile  #目标名称
mytarget.commands = @echo > $$mytarget.target #产生目标命令，windows下好像没有 类似touch的命令
mytarget.depends = mytarget2 #说明目标的依赖项

mytarget2.commands = @echo Building $${mytarget.target}

QMAKE_EXTRA_TARGETS += mytarget mytarget2 #另外定义两个目标

