TEMPLATE = subdirs
#ָ������Ŀ����������˳�򹹽�
CONFIG += ordered

#��ָ������Ŀ��Ŀ¼���� .pro�ļ�������Ŀ¼������ͬ if the subdirectory is called myapp,
#the project file in that directory should be called myapp.pro.
#Ҳ��ֱ��ָ�� pro�ļ�������������ô��
SUBDIRS += \
    firstLevel1 \
    firstlevel2/static.pro
