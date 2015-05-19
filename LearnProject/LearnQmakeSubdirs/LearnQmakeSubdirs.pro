TEMPLATE = subdirs
#指定子项目按照声明的顺序构建
CONFIG += ordered

#若指定子项目的目录，则 .pro文件必须与目录名称相同 if the subdirectory is called myapp,
#the project file in that directory should be called myapp.pro.
#也可直接指定 pro文件，但不建议这么做
SUBDIRS += \
    firstLevel1 \
    firstlevel2/static.pro
