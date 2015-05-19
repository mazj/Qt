#ifndef HELPOBJECT_H
#define HELPOBJECT_H

#include <QtGlobal>
#include <QObject>

class HelpObjectPrivate;

/**
 * QObject 的帮助类，主要为了获取 QObject 的更详细信息，但这里利用了
 * QT 4.7定义的内部结构，这些结构可能是要变的
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
