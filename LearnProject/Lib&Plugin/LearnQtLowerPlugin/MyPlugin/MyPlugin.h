#ifndef MYPLUGIN_H
#define MYPLUGIN_H

#include <QObject>
#include <QtPlugin>
#include "IMyPlugin.h"

//实现插件接口
class MYPLUGINSHARED_EXPORT MyPlugin : public QObject, public IMyPlugin
{
    Q_OBJECT
    Q_INTERFACES(IMyPlugin)
#ifdef QT_5
    Q_PLUGIN_METADATA(IID "com.tianexample.MyPlugin" FILE "MyPlugin.json")
#endif

public:
    explicit MyPlugin(QObject *parent = 0);
    virtual QString echo(const QString& message);

//signals:

//public slots:

};

#endif // MYPLUGIN_H
