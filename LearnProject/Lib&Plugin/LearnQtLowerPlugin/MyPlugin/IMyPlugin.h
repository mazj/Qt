#ifndef IMYPLUGIN_H
#define IMYPLUGIN_H

#include <QString>
#include "myplugin_global.h"

//定义插件接口，肯定是抽象类了
class MYPLUGINSHARED_EXPORT IMyPlugin
{

public:
    virtual ~IMyPlugin() {}
    virtual QString echo(const QString& message) = 0;
};

// 插件接口必须用这个宏声明，第一个参数是 接口名称
//The second argument is a string that must identify the interface in a unique way.
Q_DECLARE_INTERFACE(IMyPlugin, "com.tianexample.MyPlugin");
#endif // MYPLUGIN_H
