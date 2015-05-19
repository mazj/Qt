#include <QCoreApplication>
#include <QtCore>

#include <QTextCodec>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    {
    QString s("QStringfile.conf");
    QSettings setting(s, QSettings::IniFormat);
    setting.clear();
    setting.setValue("First", 0);
    setting.setValue("First/Second", 1);
    setting.setValue("First/Second/Third", 2);
    setting.setValue("First/Second/Third/µÚËÄ", 2);
    setting.sync();

    QString ss = setting.value("wwww").toString();

    QStringList list = setting.childGroups ();
    QStringList childList = setting.allKeys();
    childList = setting.childKeys();

    setting.beginGroup(list[0]);
    list = setting.childGroups ();
    childList = setting.allKeys();
        childList = setting.childKeys();

    setting.beginGroup(list[0]);
    list = setting.childGroups ();
    childList = setting.allKeys();
    childList = setting.childKeys();

    setting.beginGroup(list[0]);
    list = setting.childGroups ();
    }

    {
        QString s("QSettingfile.conf");
        QSettings settings(s, QSettings::IniFormat);
        settings.clear();
        settings.setValue("First", 0);

        settings.beginGroup("First");

        settings.beginWriteArray("logins");
        QList<QString> logins;
        logins << "name1" << "name2" << "name3";
         for (int i = 0; i < logins.size(); ++i) {
             settings.setArrayIndex(i);
             settings.setValue("userName", logins.at(i));
         }
         settings.endArray();

         settings.beginGroup("logins");
        QStringList keys= settings.childKeys();
        settings.setValue("myKey", "myKeyValue");

         settings.endGroup();

        settings.sync();
    }

    return a.exec();
}
