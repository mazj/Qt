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
 * ���캯��
 * @param toHelpObj Ҫ�����Ķ���
 * @param parent
 */
HelpObject::HelpObject(QObject *toHelpObj, QObject *parent) :
    QObject(*new HelpObjectPrivate, parent)
{
    Q_D(HelpObject);
    d->toHelpObj = toHelpObj;
}

/**
 * ��� object�������¼�������
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
 * ��� object�������¼�������, ��debug��ӡ
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
    // ΢��ĺ���
    sprintf_s(address, sizeof(address), "(0x%p) ", object);
//    str.append(tr("(%1) ").arg(object));
    str +=address;
    str += flags;

    return str;
}



/*****************************************************************************
  QObject debugging output routines.
  Qt 4.7.3 �� QObject::dumpObjectTree() s���õĺ���,�Լ��޸�
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

/** ��ӡ obj ������ qDebug ��ӡ,
 *  �� QObject::dumpObjectTree () ������ͬ�� ���� Qobject::dumpObjectTree ()
 *  ��ӡ��Ϣ��Щ
 * ÿ�������������Ϣ��ʽΪ
 * ClassName::objectName(objectAddress) F<x,y,width,heigh> I
 * F ��ʾ�� ��ȡ�����widget
 * ֻ�� widget ���� λ�úͿ����Ϣ
 * I ��ʾ widget �����ص�
  */
void HelpObject::_dumpObjectTree(const QObject *obj)
{
    if (!obj)
        return;

    dumpObject(0, obj, true);
}

