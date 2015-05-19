#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <private/qobject_p.h>
#include <QPointer>
#include <QWidget>
#include <QApplication>

//#undef COMPILE_HELP_OBJECT
#include "HelpObject.h"

class HelpObject1 : public QObject
{
    Q_OBJECT
};

class HelpObjectPrivate : public QObjectPrivate
{
public:
    HelpObjectPrivate()
    {  }

    QObjectPrivate *getToHelpObjD()
    {
        if (toHelpObj)
        {
            return (QObjectPrivate*)(static_cast<HelpObject*>(toHelpObj.data())->d_func());
        }
        else
        {
            return NULL;
        }
    }

    QPointer<QObject> toHelpObj;

private:
//    const QObjectPrivate *pObjPrivate;
};

/**
 * 构造函数
 * @param toHelpObj 要帮助的对象
 * @param parent
 */
HelpObject::HelpObject(QObject *toHelpObj, QObject *parent) :
    QObject(*new HelpObjectPrivate, parent)
{
    Q_D(HelpObject);
    d->toHelpObj = toHelpObj;
}

/**
 * 输出 object的所有事件过滤器
 */
void HelpObject::dumpEventFilters()
{
    Q_D(HelpObject);

    QObjectPrivate * od = d->getToHelpObjD();
    if (!od)
        return;

    const QList<QPointer<QObject> > &list = od->eventFilters;
    for(int i=0; i<list.count(); i++)
    {
        dumpObject(1, list[i].data(), false);
    }
//    QPointer<QObject> obj;
//    foreach ( obj, d->pObjPrivate->eventFilters) {
//        ::dumpObject(1, obj, false);
//    }
}

/**
 * 输出 object的所有事件过滤器, 用debug打印
 */
void HelpObject::dumpEventFilters(const QObject *obj)
{
    if (obj == NULL)
        return;

    HelpObject h(const_cast<QObject*>(obj));
    h.dumpEventFilters();
}

QString HelpObject::getObjectSimpleDescription(const QObject *object)
{
    if (!object)
        return QString();

    QString name = object->objectName();
    QString flags = QLatin1String("");
#if 1
    if (qApp->focusWidget() == object)
        flags += 'F';
    if (object->isWidgetType()) {
        QWidget * w = (QWidget *)object;
        if (w->isVisible()) {
            QString t("<%1,%2,%3,%4>");
            flags += t.arg(w->x()).arg(w->y()).arg(w->width()).arg(w->height());
        } else {
            flags += 'I';
        }
    }
#endif


    QString str;
    str = object->metaObject()->className();
    str += "::";
    str +=name;

    char address[128] = {0};
//    sprintf_s()
    // 微软的函数
    sprintf_s(address, sizeof(address), "(0x%p) ", object);
//    str.append(tr("(%1) ").arg(object));
    str +=address;
    str += flags;

    return str;
}



/*****************************************************************************
  QObject debugging output routines.
  Qt 4.7.3 的 QObject::dumpObjectTree() s所用的函数,稍加修改
 *****************************************************************************/
void HelpObject::dumpObject(int level, const QObject *object, bool recursive)
{
    if (!object)
        return;

#ifndef QT_NO_DEBUG_OUTPUT
    if (object) {
        QByteArray buf;
        buf.fill(' ', level / 2 * 8);
        if (level % 2)
            buf += "    ";

        qDebug("%s%s", (const char*)buf,
               getObjectSimpleDescription(object).toLocal8Bit().data());
        if (recursive)
        {
            QObjectList children = object->children();
            if (!children.isEmpty()) {
                for (int i = 0; i < children.size(); ++i)
                    dumpObject(level+1, children.at(i), recursive);
            }
        }

    }
#else
    Q_UNUSED(level)
        Q_UNUSED(object)
#endif
}

/** 打印 obj 树，用 qDebug 打印,
 *  与 QObject::dumpObjectTree () 功能相同， 但比 Qobject::dumpObjectTree ()
 *  打印信息多些
 * 每个对象的描述信息格式为
 * ClassName::objectName(objectAddress) F<x,y,width,heigh> I
 * F 表示是 获取焦点的widget
 * 只有 widget 才有 位置和宽高信息
 * I 表示 widget 是隐藏的
  */
void HelpObject::_dumpObjectTree(const QObject *obj)
{
    if (!obj)
        return;

    dumpObject(0, obj, true);
}

