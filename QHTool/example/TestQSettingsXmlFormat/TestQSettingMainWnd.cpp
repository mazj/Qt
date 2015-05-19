#include "TestQSettingMainWnd.h"
#include "ui_MainWindow.h"

#include <QSettings>
#include <QFile>
#include <QDebug>
#include <QHTool/qhXml.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
#if 1
    {
        EQHEncode encode = EQHEncodeGBK;
    QSettings::Format xmlformat = qhGetQSettingsXmlFormat(encode);
    QSettings s("../TestQSettingsXmlFormat/test.xml", xmlformat);
    QStringList keys = s.allKeys();
    s.setValue("dido_config_table/device/commonDevice/di/board_type_1/NULL", 257);
    s.setValue("dido_config_table/device/OtherDevice/di/board_type_1/_1", QString::fromLocal8Bit("汉字"));
    s.setValue("dido_config_table/device/OtherDevice/di/board_type_1/NULL", "");
    s.remove("dido_config_table/device/commonDevice/di/board_type_1/NULL");
    }
    {
        EQHEncode encode = EQHEncodeGBK;
        QSettings::Format xmlformat = qhGetQSettingsXmlFormat(encode);
    }



//    QStringList keyss = s.childKeys();
//    foreach (QString ss, keyss) {
//        qDebug() << ss << ":" << s.value(ss);
//        s.setValue(ss, s.value(ss).toString()+"_modify");
//    }
//    QStringList keys = s.childGroups ();
//    foreach (QString ss, keys) {
//        qDebug() << ss << ":" << s.value(ss);
//    }
//    s.beginGroup(keys[0]);
//    keyss = s.childKeys();
//    foreach (QString ss, keyss) {
//        qDebug() << ss << ":" << s.value(ss);
//    }
//    s.endGroup();
#endif

    //*******{ 测试对队列的支持
    {

    //QFile::remove(tr("QSettingsXmlFormatTestTmp1.xml"));
    QSettings s1("QSettingsXmlFormatTestTmp1.xml", QSettings::IniFormat);
    s1.beginGroup("root");
//    s1.beginWriteArray("logins");
//    s1.setArrayIndex(6);
//    s1.setValue("userName", "name6");
//    QList<QString> logins;
//    logins << "name1" << "name2" << "name3";
//     for (int i = 0; i < logins.size(); ++i) {
//         s1.setArrayIndex(i);
//         s1.setValue("userName", logins.at(i));
//     }
//     s1.endArray();

     int aSize = s1.beginReadArray("logins");
     qDebug() << "logins size = " << aSize;
     for (int i = 0; i < aSize; ++i) {
         s1.setArrayIndex(i);
         if (s1.value("userName").toString().isNull())
         {
             qDebug() << "ArrayIndex " << i << " isNUll";
         }
         qDebug() << "ArrayIndex " << i << "=" << s1.value("userName").toString(); //s1.value("userName");
     }
     s1.endArray();


     s1.setValue("testKey", "testKey值");
     s1.setValue("testKeyEmpty", "");

     s1.endGroup();
     s1.sync();
     }
    {
        QSettings s1("QSettingsXmlFormatTestTmp1.xml", QSettings::IniFormat);
        s1.beginGroup("root");
        QStringList allKeys = s1.allKeys();
        qDebug() << allKeys;

        QStringList childKeys = s1.childKeys();
        qDebug() << childKeys;

        QStringList childGroup = s1.childGroups();
        qDebug() << childGroup;

        s1.beginGroup("logins");
        childKeys = s1.childKeys();
                qDebug() << childKeys;


          s1.endGroup();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
