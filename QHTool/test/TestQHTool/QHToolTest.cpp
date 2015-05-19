#include "QHToolTest.h"


#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include <QComboBox>
#include <QDomDocument>

#include "QHTool/qHelpFunction.h"
#include "QHTool/qhXml.h"

QHToolTest::QHToolTest()
{
}

void QHToolTest::initTestCase()
{
}

void QHToolTest::cleanupTestCase()
{
}




void QHToolTest::test_qhQStringFindLineEndPos()
{
    QString str;
    QVERIFY(qhQStringFindLineEndPos(str) == -1);

    str = QString("1234567890");
    QVERIFY(qhQStringFindLineEndPos(str) == -1);

    str = QString("123456\n7890");
    QVERIFY(qhQStringFindLineEndPos(str) == 6);

    str = QString("123456\n7890");
    QVERIFY(qhQStringFindLineEndPos(str, 2) == 6);
}

void QHToolTest::test_qhRemoveExegesisInCode()
{
    QString code =
    "int f()\n\
    {\n\
        int o; // eggr\n\
        if (1) //rr /*   wrrr  */\n\
        {\
            /*  //gggg\
           int n = 90;\
    */\n\
        }\
    }";

    QString _code =
     qhRemoveExegesisInCode(code);
    qDebug() << "\nobserve:" << _code;

    QString fileName("../TestQHTool/TestFile/testCpp.cpp");
    QFile cppFile(fileName);
    QFile::remove(fileName+".cpp");
    QH_VERIFY( cppFile.open(QIODevice::Text | QIODevice::ReadOnly) );
    QTextStream s(&cppFile);
    _code = s.readAll();
    qhRemoveExegesisInCode_(_code);
    QFile outfile(fileName+".cpp");
    QH_VERIFY( outfile.open(QIODevice::Text | QIODevice::WriteOnly) );
    QTextStream outS(&outfile);
    outS << _code;
    qDebug() << "\nobserve:" << fileName+".cpp";
}

void QHToolTest::test_qhGetEnumMap()
{
    enum MyEnum {
        E0,
         E1,  //fefe
         E2 = 4, /*
         E3,*/
         E4 = E2,
        E5 = 1+2,
        E6 = E2 | E1};

    QMap<int, QString> map = QH_GET_ENUM_MAP(E_I(QSizePolicy::Minimum),
                                             E_I(E1),
                                             E_I(E2),
                                             E_I(E4),
                                             E_I(E5),
                                             E_I(E6));
    qDebug() << "observe:\n" << map;

    map = qhGetEnumMap(
                QH_GET_CODE(
                    enum MyEnum {
                        E0,
                         E1,  //fefe
                         E2 = 4, /*
                         E3,*/
                         E4 = E2,
                        E5 = 1+2,
                        E6 = E2 | E1}),
                QH_GET_ENUM_MAP(E_I(E5), E_I(E6)) );
//                       QH_GET_ENUM_MAP(E_I(E5), E_I(E5), E_I(E6)) );

    qDebug() << "observe:\n" << map;

    QMap<int, QString> map3 = qhGetEnumMap(
                  QH_GET_CODE(
      enum Policy {
          Fixed = 0,
          Minimum = QSizePolicy::GrowFlag,
          Maximum = QSizePolicy::ShrinkFlag,
          Preferred = QSizePolicy::GrowFlag | QSizePolicy::ShrinkFlag,
          MinimumExpanding = QSizePolicy::GrowFlag | QSizePolicy::ExpandFlag,
          Expanding = QSizePolicy::GrowFlag | QSizePolicy::ShrinkFlag | QSizePolicy::ExpandFlag,
          Ignored = QSizePolicy::ShrinkFlag | QSizePolicy::GrowFlag | QSizePolicy::IgnoreFlag
                      }),
                  QH_GET_ENUM_MAP(E_I(QSizePolicy::Minimum),
                                   E_I(QSizePolicy::Maximum),
                                   E_I(QSizePolicy::Preferred),
                                   E_I(QSizePolicy::MinimumExpanding),
                                   E_I(QSizePolicy::Expanding),
                                  E_I(QSizePolicy::Ignored)
                                   ) );

    qDebug() << "observe:\n" << map3;

}

void QHToolTest::test_qhDomFindElement()
{
    QDomDocument doc;
    QString errStr;
    int errLine;
    int errCol;
    QString str(
    "<first>firstText"
        "<second>secondText1"
            "<third>thirdText1</third>"
            "<third>thirdText2</third>"
        "</second>"
        "<second>secondText2"
            "<third>thirdText3</third>"
            "<third>thirdText4</third>"
        "</second>"
    "</first>");
    if (!doc.setContent(str, &errStr, &errLine, &errCol))
    {
        qCritical() << __FUNCTION__ << ": " << errStr << "at line "
                   << errLine << " column " << errCol;
        return;
    }

    QDomElement root = doc.documentElement();
    QList<QString> l;
     QDomElement ele;

    /**
      测试 qhDomFindElement
      \@{
      */

    l.push_back("second");
    l.push_back("third");
    ele = qhDomFindElement(root, l);
    QVERIFY(!ele.isNull());
    QVERIFY(ele.tagName()=="third");
    QVERIFY(ele.firstChild().toText().data()=="thirdText1");

    l.clear();
    l.push_back("second");
    ele = qhDomFindElement(root, l);
    QVERIFY(!ele.isNull());
    QVERIFY(ele.tagName()=="second");
    QVERIFY(ele.firstChild().toText().data()=="secondText1");

    //错误测试

    l.clear();
    l.push_back("second");
    l.push_back("third1");
    ele = qhDomFindElement(root, l);
    QVERIFY(ele.isNull());

    l.clear();
    l.push_back("second");
    l.push_back("third");
    l.push_back("forth");
    ele = qhDomFindElement(root, l);
    QVERIFY(ele.isNull());

    l.clear();
    l.push_back("second1");
    l.push_back("third1");
    l.push_back("forth");
    ele = qhDomFindElement(root, l);
    QVERIFY(ele.isNull());

    l.clear();
    l.push_back("second1");
    ele = qhDomFindElement(root, l);
    QVERIFY(ele.isNull());

    QString docStr = doc.toString(0);
    /**
      测试 qhDomFindElement
      \@}
      */

    /**
      测试 qhDomFindElements
      \@{
      */
    QList<QDomElement> eleList;
     l.clear();
    l.push_back("second");
    l.push_back("third");
    eleList = qhDomFindElements(root, l);
    QVERIFY(!eleList.isEmpty());
    QVERIFY(eleList.size()==4);

    for(int i=0; i<eleList.size(); i++)
    {
        QVERIFY(eleList[i].tagName()=="third");
        QString data = eleList[i].firstChild().toText().data();
        QVERIFY(data == QString("thirdText%1").arg(i+1));
    }

    //错误测试
    l.clear();
    eleList.clear();
   l.push_back("second1");
   l.push_back("third");
   eleList = qhDomFindElements(root, l);
   QVERIFY(eleList.isEmpty());

   l.clear();
   eleList.clear();
  l.push_back("second");
  l.push_back("third1");
  eleList = qhDomFindElements(root, l);
  QVERIFY(eleList.isEmpty());
    /**
      测试 qhDomFindElements
      \@}
      */

  /**
    测试qhDomFindText
    \@{
    */
  QDomText dt = qhDomFindText(root, "firstText");
  QVERIFY(!dt.isNull());
  QVERIFY(dt.data() == "firstText");
  dt = qhDomFindText(root, "firstText1");
  QVERIFY(dt.isNull());
  /**
    测试qhDomFindText
    \@}
    */
}

void QHToolTest::test_qhGetQSettingsXmlFormat_data()
{
    QTest::addColumn<int>("textcodec");
    QTest::newRow("gbk") << int(EQHEncodeGBK);
    QTest::newRow("utf8") << int(EQHEncodeUTF8);
    QTest::newRow("utf16") << int(EQHEncodeUTF16);
}

void QHToolTest::test_qhGetQSettingsXmlFormat()
{
    QTextCodec * codec = QTextCodec::codecForName("GBK");
    SettingTextCodec stc(codec, codec, codec);

    QFETCH(int, textcodec);
    {
        QFile::remove(tr("../TestQHTool/QSettingsXmlFormatTestTmp.xml"));
        QVERIFY( QFile::copy(tr("../TestQHTool/QSettingsXmlFormatTest.xml"),
                             tr("../TestQHTool/QSettingsXmlFormatTestTmp.xml")) );
        EQHEncode encode = intToEQHEncode(textcodec);
        QSettings::Format xmlformat = qhGetQSettingsXmlFormat(encode);
        QVERIFY(xmlformat != QSettings::IniFormat);
        QSettings s("../TestQHTool/QSettingsXmlFormatTestTmp.xml", xmlformat);

        QStringList keys = s.allKeys();
        QVERIFY(keys.size() == 9);
        QStringList groups = s.childGroups ();
        QVERIFY(groups.size() == 1);
        keys = s.childKeys ();
        QVERIFY(keys.size() == 1);

        s.beginGroup("dido_config_table");
        keys = s.childKeys ();
        QVERIFY(keys.size() == 1);
        s.endGroup();

        QVERIFY(s.value("dido_config_table").toString() == "dido_config_table data");

        QVERIFY(s.value("dido_config_table/device/OtherDevice").toString() ==
                QString("OtherDevice数据"));

        QString hanzi("汉字");
        QVERIFY(s.value("dido_config_table/device/OtherDevice/di/board_type_1/_1").toString() ==
                hanzi);
        QVERIFY(s.value("dido_config_table/device/OtherDevice/di/board_type_1/_2").toString() ==
                QString::fromLatin1("English"));
        QVERIFY(s.value("dido_config_table/device/OtherDevice/di/board_type_1/intnumber").toInt() ==
                12345);
        float f = s.value("dido_config_table/device/OtherDevice/di/board_type_1/float").toFloat();
        QVERIFY( f>=12.344 && f<=12.346);
        QVERIFY(s.value("dido_config_table/device/OtherDevice1").toString() ==
                QString("OtherDevice1 值"));
        QVERIFY(s.value("dido_config_table/device1").toString() ==
                QString("device1 Vaule"));


        s.setValue("dido_config_table/device1", QString("device1 Setted Vaule"));
        QVERIFY(s.value("dido_config_table/device1").toString() ==
                QString("device1 Setted Vaule"));

        s.setValue("dido_config_table/device/OtherDevice1",
                        QString("OtherDevice1 设置的 值"));
        QVERIFY(s.value("dido_config_table/device/OtherDevice1").toString() ==
                QString("OtherDevice1 设置的 值"));

        s.setValue("dido_config_table/device/OtherDevice2",
                        QString("OtherDevice2 设置的 值"));
        QVERIFY(s.value("dido_config_table/device/OtherDevice2").toString() ==
                QString("OtherDevice2 设置的 值"));

        //*******{ 测试对队列的支持
        {

        QFile::remove(tr("../TestQHTool/QSettingsXmlFormatTestTmp1.xml"));
        QSettings s1("../TestQHTool/QSettingsXmlFormatTestTmp1.xml", xmlformat);
        s1.beginGroup("root");

        s1.beginWriteArray("logins");

        s1.setArrayIndex(6);
        s1.setValue("userName", "name7");

        QList<QString> logins;
        logins << "name1" << "name2" << "name3" ;
         for (int i = 0; i < logins.size(); ++i) {
             s1.setArrayIndex(i);
             s1.setValue("userName", logins.at(i));
         }

         s1.setArrayIndex(4);
         s1.setValue("userName", "name5");

         s1.endArray();

         s1.setValue("testKey", "testKey值");
         s1.setValue("testKeyEmpty", "");
         s1.endGroup();
         s1.sync();
         }
        {
            QSettings s1("../TestQHTool/QSettingsXmlFormatTestTmp1.xml", xmlformat);
            s1.beginGroup("root");

            QStringList keys = s1.allKeys();
            int count = s1.beginReadArray("logins");
            QVERIFY(count == 7);
            for(int i=0; i<count; ++i)
            {
                s1.setArrayIndex(i);
                QString str = s1.value("userName").toString();
                if (i == 3 || i == 5)
                {
                    QVERIFY(str.isNull());
                }
                else
                {
                    QVERIFY( str == QString("name%1").arg(i+1) );
                }
            }
            s1.endArray();

            QVERIFY( s1.value("testKey").toString() == QString("testKey值") );
            QVERIFY( s1.value("testKeyEmpty").toString() == QString("") ); //测试空字符串
            s1.endGroup();
        }
         //*******} 测试对队列的支持

        // 测试多次注册
        for(int i=0; i<100; i++)
            QVERIFY(qhGetQSettingsXmlFormat( encode) != QSettings::IniFormat);
    }

}

void QHToolTest::test_qhIsQSettingsXmlFormatFile()
{
    QString errInfo;
    errInfo.clear();
    QVERIFY (qhIsQSettingsXmlFormatFile("../TestQHTool/QSettingsXmlFormatTest.xml", errInfo));
    //qDebug() << errInfo;

    errInfo.clear();
    QVERIFY (!qhIsQSettingsXmlFormatFile("../TestQHTool/QSettingsXmlFormatTestErr1.xml", errInfo));
    qDebug() << "\nobserve:" << errInfo;

    errInfo.clear();
    QVERIFY (!qhIsQSettingsXmlFormatFile("../TestQHTool/QSettingsXmlFormatTestErr2.xml", errInfo));
    qDebug() << "\nobserve:" << errInfo;

    errInfo.clear();
    QVERIFY (!qhIsQSettingsXmlFormatFile("../TestQHTool/QSettingsXmlFormatTestErr3.xml", errInfo));
    qDebug() << "\nobserve:" << errInfo;

}

void QHToolTest::test_HelpQChar()
{
    // test qhQCharIs16Number
     // test qhQCharToNumber
    QChar c;
     int num;

    c= '0';
    QVERIFY( qhQCharIs16Number(c) );
    num = qhQCharToNumber(c);
    QVERIFY( num==0 );
    num = qhQCharToNumber(c, 16);
    QVERIFY( num==0 );

    c= '9';
    QVERIFY( qhQCharIs16Number(c) );
    num = qhQCharToNumber(c);
    QVERIFY( num==9 );
    num = qhQCharToNumber(c, 16);
    QVERIFY( num==9 );

    c= 'a';
    QVERIFY( qhQCharIs16Number(c) );
    num = qhQCharToNumber(c, 10);
    QVERIFY( num==-1 );
    num = qhQCharToNumber(c, 16);
    QVERIFY( num==10 );


    c= 'A';
    QVERIFY( qhQCharIs16Number(c) );
    num = qhQCharToNumber(c, 10);
    QVERIFY( num==-1 );
    num = qhQCharToNumber(c, 16);
    QVERIFY( num==10 );


    c= 'f';
    QVERIFY( qhQCharIs16Number(c) );
    num = qhQCharToNumber(c, 16);
    QVERIFY( num==15 );
    num = qhQCharToNumber(c, 10);
    QVERIFY( num==-1 );

    c= 'F';
    QVERIFY( qhQCharIs16Number(c) );
    num = qhQCharToNumber(c, 16);
    QVERIFY( num==15 );
    num = qhQCharToNumber(c, 10);
    QVERIFY( num==-1 );

    c= ' ';
    QVERIFY( !qhQCharIs16Number(c) );
    num = qhQCharToNumber(c);
    QVERIFY( num==-1 );

    c= 'q';
    QVERIFY( !qhQCharIs16Number(c) );
    num = qhQCharToNumber(c);
    QVERIFY( num==-1 );
    num = qhQCharToNumber(c, 16);
    QVERIFY( num==-1 );

    num = qhQCharToNumber(QChar('3'), 17);
    QVERIFY( num==-1 );
}

void QHToolTest::test_HelpQString()
{
    //int qhQString2Int(const QString& str, int from=0, int* end=NULL, bool *successful = NULL, int base = 10);
    //int qhQStringFindLineEndPos(const QString & str, int from = 0);
    {
    QString str;
    int pos;
    str = "012345\n67\n8";
    pos = qhQStringFindLineEndPos(str, 0);
    QVERIFY(pos == 6);
    pos = qhQStringFindLineEndPos(str, 2);
    QVERIFY(pos == 6);
    pos = qhQStringFindLineEndPos(str, 7);
    QVERIFY(pos == 9);

    str = "012345\r67\n8";
    pos = qhQStringFindLineEndPos(str, 0);
    QVERIFY(pos == 6);
    pos = qhQStringFindLineEndPos(str, 2);
    QVERIFY(pos == 6);

    str = "012345\r\n67\n8";
    pos = qhQStringFindLineEndPos(str, 0);
    QVERIFY(pos == 7);
    pos = qhQStringFindLineEndPos(str, 2);
    QVERIFY(pos == 7);
    }

    {
        bool ret;
        int end;
        int num;

        // 10 进制测试
        qhQString2Int(QString("qsw23rf"),1, 10, NULL, &ret);
        QVERIFY(!ret);

        num = qhQString2Int(QString("qsw23rf"),3, 10, &end, &ret);// 会转化成功，返回23，end返回5
        QVERIFY(ret);
        QVERIFY(num == 23);
        QVERIFY(end == 5);

        num = qhQString2Int(QString("qsw2333rf"),4, 10, &end, &ret);// 会转化成功，返回333，end返回7
        QVERIFY(ret);
        QVERIFY(num == 333);
        QVERIFY(end == 7);

        num = qhQString2Int(QString("qsw 23rf"),3, 10, &end, &ret);// 会转化成功，返回23，end返回6
        QVERIFY(ret);
        QVERIFY(num == 23);
        QVERIFY(end == 6);

        num = qhQString2Int(QString("qswe13frf"),3, 10, &end, &ret);
        QVERIFY(!ret);

        num = qhQString2Int(QString("qsw 13frf"),3, 10, &end, &ret);
        QVERIFY(ret);
        QVERIFY(num == 13);
        QVERIFY(end == 6);

        // 16进制 测试
        num = qhQString2Int(QString("qsw 1frf"),3, 16, &end, &ret);
        QVERIFY(ret);
        QVERIFY(num == 16+15);
        QVERIFY(end == 6);

        num = qhQString2Int(QString("qsw 12rf"),3, 16, &end, &ret);
        QVERIFY(ret);
        QVERIFY(num == 16+2);
        QVERIFY(end == 6);

        // 8进制 测试
        num = qhQString2Int(QString("qswe1frf"),3, 8, &end, &ret);
        QVERIFY(!ret);

        num = qhQString2Int(QString("qsw 1frf"),3, 8, &end, &ret);
        QVERIFY(ret);
        QVERIFY(num == 1);
        QVERIFY(end == 5);

        num = qhQString2Int(QString("qsw 199rf"),3, 8, &end, &ret);
        QVERIFY(ret);
        QVERIFY(num == 1);
        QVERIFY(end == 5);

        num = qhQString2Int(QString("qsw 12rf"),3, 8, &end, &ret);
        QVERIFY(ret);
        QVERIFY(num == 8+2);
        QVERIFY(end == 6);

        // 数字在结尾测试
        num = qhQString2Int(QString("qsw 12"),3, 16, &end, &ret);
        QVERIFY(ret);
        QVERIFY(num == 16+2);
        QVERIFY(end == 6);

    }
}

void QHToolTest::test_HelpQFile()
{
    //QString& qhReadQFileString(const QString& filePath, QString& content);
    {
        QString fileName("../TestQHTool/TestFile/existedFile.txt");
        QString shouldS = QString::fromLocal8Bit("1234567890-=我是中国人");
        Q_ASSERT( QFile::exists(fileName) );
        QString content;
        qhReadQFileString(fileName, content);
        QVERIFY(content == shouldS);
    }

//    bool qhWriteQFileString(const QString& filePath, const QString &content,
//                            QTextCodec * codec)
    {
        QString fileName("../TestQHTool/TestFile/existedFile1.txt");
        Q_ASSERT( QFile::exists(fileName) );
        QString content = QString::fromLocal8Bit("我是中国人1234567890-=54tgenen");
        bool ret = qhWriteQFileString(fileName, content);
        QVERIFY(ret);
        qDebug() << "\nobserve:" << fileName;

        fileName = ("../TestQHTool/TestFile/notExistedFile.txt");
        QFile::remove(fileName);
        Q_ASSERT( !QFile::exists(fileName) );
        content = QString::fromLocal8Bit("我是中国人1234567890-=54tgenen");
        ret = qhWriteQFileString(fileName, content);
        QVERIFY(ret);
        qDebug() << "\nobserve:" << fileName;

    }
}

void QHToolTest::test_convertCCodeString()

{
    QString fileName("../TestQHTool/TestFile/cppstr.txt");

    QString str("1244\n\r\t  \1 \x0A");
    QString content;
    qhReadQFileString(fileName, content);
    qhConvertCCodeString(content);
    QVERIFY(content == str);
}

// test_qhQListContainRepeatEle
void QHToolTest::test_uniqueQList()
{
    QList<int> l;
    QSet<int> repeat;
    int n = 0;

    l.push_back(n++);
    l.push_back(n++);
    l.push_back(n++);
    l.push_back(n++);
    l.push_back(n++);
    l.push_back(n++);

    QList<int> _l(l);
    QVERIFY(qhQListContainRepeatEle(l, &repeat) == false);
    QVERIFY(repeat.isEmpty());
    QVERIFY(qhQListContainRepeatEle(l) == false);

    qhUniqueQList(l);
    QVERIFY(l == _l);

    l.clear();
    repeat.clear();
    n = 0;
    l.push_back(100);
    l.push_back(n++); //0
    l.push_back(n++); //1
    l.push_back(n++); //2
    l.push_back(1);
    l.push_back(n++);
    l.push_back(1);
    l.push_back(100);

    QVERIFY(qhQListContainRepeatEle(l, &repeat) == true);
    QVERIFY(!repeat.isEmpty());
    QVERIFY(repeat.size() == 2);
    QVERIFY(repeat.contains(0));
    QVERIFY(repeat.contains(7));
    QVERIFY(qhQListContainRepeatEle(l));

    qhUniqueQList(l);
    QVERIFY(l.size() == 5);
    QVERIFY(l[0] == 100);
    QVERIFY(l[1] == 0);
    QVERIFY(l[2] == 1);
    QVERIFY(l[3] == 2);
    QVERIFY(l[4] == 3);
}

void QHToolTest::test_qhQListReplace()
{
    QList<int> l;
    int n = 0;

    l.push_back(n++);
    l.push_back(n++);
    l.push_back(n++);
    l.push_back(n++);
     l.push_back(2);
    l.push_back(n++);

    QList<int> l2(l);

    QVERIFY( qhQListReplace(l, 2, 5) ); // 检测返回值
    QVERIFY(l.size() == l2.size()); //检测元素个数不能变

    for (int i = 0; i < l.size(); ++i) {
        if (l2[i] == 2) // 检测 该替换的必须替换
        {
            QVERIFY(l[i] == 5);
        }
        else // 检测 不该替换的一个也不能替换
        {
            QVERIFY(l[i] == l2[i]);
        }
    }


    l2 = l;
    QVERIFY( !qhQListReplace(l, 2, 5) ); // 检测返回值
    QVERIFY(l == l2);   //检测：返回假的情况下 必须不能改变list

}
