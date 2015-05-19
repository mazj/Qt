#ifndef HELPOBJECT_H
#define HELPOBJECT_H

#include <QtGlobal>
#include <QObject>

class HelpObjectPrivate;

/**
 * QObject �İ����࣬��ҪΪ�˻�ȡ QObject �ĸ���ϸ��Ϣ��������������
 * QT 4.7������ڲ��ṹ����Щ�ṹ������Ҫ���
 */
class HelpObject : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HelpObject)

public:
    explicit HelpObject(QObject *toHelpObj, QObject *parent = 0);
    void dumpEventFilters();

//static
public:
    static void dumpEventFilters(const QObject *obj);
    static void _dumpObjectTree(const QObject *obj);
    static QString getObjectSimpleDescription(const QObject *obj);
    static void dumpObject(int level, const QObject *object, bool recursive);

//signals:

//public slots:

};

#ifdef COMPILE_HELP_OBJECT
#include "HelpObject.cpp"
//#include "moc_HelpObject.cpp"
#endif


#endif // HELPOBJECT_H
