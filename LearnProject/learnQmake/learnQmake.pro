#-------------------------------------------------
#
# Project created by QtCreator 2014-05-22T16:29:06
#
#-------------------------------------------------

# Ҫ�õ��� qtģ��
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# ���ɵ�Ӧ�ó�������
TARGET = learnQmake
#����Ӧ�ó�������
TEMPLATE = app


SOURCES += main.cpp\
        LearnQmakeMainWindow.cpp

HEADERS  += LearnQmakeMainWindow.h

FORMS    += LearnQmakeMainWindow.ui

# �ҷ��� �� windows qt5.2 �У��� CONFIG �в�ָ�� debug �� release����Ĭ��
# ͬʱ��� debug �� release�ģ����� ���� makefile�� Makefile Makefile.debug
# Makefile.release
# �� manual �� qmake�� Variables���֣�When you use the debug_and_release option (which is the default under Windows),


# �� CONFIG �� ͬʱ���� debug �� releaseѡ��ʱ��ֻ����һ��ѡ���ǵ�ǰ����ġ����� CONFIG�бȽ�����
# 1��һ�飬ֻ���ж� CONFIG �� �Ƿ��� debug �� releaseѡ���ǰ���ܼ����Ǹ�ѡ��
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

# 2 ��飬Ҫ���� debug �� releaseѡ����жϵ�ǰ��������ĸ�ѡ��
#begin 2
#��һ�������жϼ����ѡ� �ڶ��������жϺ��е�ѡ��
CONFIG(debug, debug|release) {
    message(2 Debug build!)
}

CONFIG(release, debug|release) {
    message(2 release build!)
}

#end 2

# install ��װ������Ϣ��ͨ��ִ�� make install �� jom.exe install ִ��
CONFIG(debug, debug|release) {
    target.path = $$PWD/debug_bin # ָ����װĿ¼
} else:CONFIG(release, debug|release) {
    target.path = $$PWD/bin       # ����qamke���ñ��� PWD
# $$OUT_PWD makefile�ļ�����·��
# $$PWD   ��ǰ��pro�ļ�����·��
    message(target.path = bin!)
}

target.file = $$TARGET   # ָ����װ�ļ�
INSTALLS += target

#����֪���� qmake������Ҫ���þ��ǲ��� makefile,�� makefile �Ļ���������
# Ŀ�� ���� ���Ĭ�ϵ�һ��Ŀ���ǲ�����Ŀ����ļ�����ִ���ļ����߿⣩��
# INSTALLS ����ָ������ install Ŀ����������Ŀ�꣬�����Ҫ������������Ŀ��
# ��Ҫʹ�� QMAKE_EXTRA_TARGETS����

mytarget.target = mytargetfile  #Ŀ������
mytarget.commands = @echo > $$mytarget.target #����Ŀ�����windows�º���û�� ����touch������
mytarget.depends = mytarget2 #˵��Ŀ���������

mytarget2.commands = @echo Building $${mytarget.target}

QMAKE_EXTRA_TARGETS += mytarget mytarget2 #���ⶨ������Ŀ��

