#ifndef XMLSETTINGS_H
#define XMLSETTINGS_H

#include <QSettings>

// ����ຯ��ʵ��û��ʹ��
class XmlSettings : public QSettings
{
    Q_OBJECT
public:
    explicit XmlSettings(const QString & fileName,
                         const QString & extension = QString("xml"),
                         QObject * parent = 0 );

//signals:

//public slots:
private:
    bool xmlReadFunc(QIODevice &device, QSettings::SettingsMap &settingsMap);
    bool xmlWriteFunc(QIODevice &device, const QSettings::SettingsMap &map);

    static QSettings::Format getQSettingsXmlFormat(const QString & extension);
};

#endif // XMLSETTINGS_H
