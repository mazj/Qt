#include "MyPlugin.h"

MyPlugin::MyPlugin(QObject *parent) :
    QObject(parent)
{
}

QString MyPlugin::echo(const QString &message)
{
    return message;
}

#ifdef QT_4
// 在插件实现类的实现中，用这个宏
// 第一个参数时项目的 TARGET名称，第二个是 类名
Q_EXPORT_PLUGIN2(MyPlugin, MyPlugin)
#endif
