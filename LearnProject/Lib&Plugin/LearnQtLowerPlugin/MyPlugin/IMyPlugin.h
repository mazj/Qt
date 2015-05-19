#ifndef IMYPLUGIN_H
#define IMYPLUGIN_H

#include <QString>
#include "myplugin_global.h"

//�������ӿڣ��϶��ǳ�������
class MYPLUGINSHARED_EXPORT IMyPlugin
{

public:
    virtual ~IMyPlugin() {}
    virtual QString echo(const QString& message) = 0;
};

// ����ӿڱ������������������һ�������� �ӿ�����
//The second argument is a string that must identify the interface in a unique way.
Q_DECLARE_INTERFACE(IMyPlugin, "com.tianexample.MyPlugin");
#endif // MYPLUGIN_H
