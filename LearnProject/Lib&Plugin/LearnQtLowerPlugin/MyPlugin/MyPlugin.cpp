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
// �ڲ��ʵ�����ʵ���У��������
// ��һ������ʱ��Ŀ�� TARGET���ƣ��ڶ����� ����
Q_EXPORT_PLUGIN2(MyPlugin, MyPlugin)
#endif
