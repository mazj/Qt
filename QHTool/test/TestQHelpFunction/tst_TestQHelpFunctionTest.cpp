#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include <QComboBox>
#include <QDomDocument>

#include "QHTool/qHelpFunction.h"

class TestQHelpFunctionTest : public QObject
{
    Q_OBJECT

public:
    TestQHelpFunctionTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void test_qhFindStrInComboBox();
    void test_qhGetComboBoxAllItemtext();
//    qhSetComboBoxValue()  //

    // QTableWidget
    void test_qhGetQTableWidgetAllItem();

    void test_qhFindLineEndPos();
    void test_qhRemoveExegesisInCode();
    void test_qhGetEnumMap();
    void test_qhDomFindElement();
    void test_qhGetQSettingsXmlFormat();
};

TestQHelpFunctionTest::TestQHelpFunctionTest()
{
}

void TestQHelpFunctionTest::initTestCase()
{
}

void TestQHelpFunctionTest::cleanupTestCase()
{
}

void TestQHelpFunctionTest::test_qhFindStrInComboBox()
{
    QComboBox com;
    com.addItem("1");
    com.addItem("abc");
    com.addItem(" ");
    com.addItem("");
    QVERIFY(qhFindStrInComboBox(&com, "1") == 0);
    QVERIFY(qhFindStrInComboBox(&com, "abc") == 1);
    QVERIFY(qhFindStrInComboBox(&com, " ") == 2);
    QVERIFY(qhFindStrInComboBox(&com, "") == 3);
    QVERIFY(qhFindStrInComboBox(&com, "no String") == -1);
}

void TestQHelpFunctionTest::test_qhGetComboBoxAllItemtext()
{
    QComboBox com;
    QStringList l;
    l << QString("1") << QString("abc");
    l << QString(" ") << QString("");
    com.addItems(l);

    QStringList l2;
    l2 = qhGetComboBoxAllItemtext(&com);

    QVERIFY(l == l2);
}

// empty
void TestQHelpFunctionTest::test_qhGetQTableWidgetAllItem()
{
}

void TestQHelpFunctionTest::test_qhFindLineEndPos()
{
    QString str;
    QVERIFY(qhFindLineEndPos(str) == -1);

    str = QString("1234567890");
    QVERIFY(qhFindLineEndPos(str) == -1);

    str = QString("123456\n7890");
    QVERIFY(qhFindLineEndPos(str) == 6);

    str = QString("123456\n7890");
    QVERIFY(qhFindLineEndPos(str, 2) == 6);
}

void TestQHelpFunctionTest::test_qhRemoveExegesisInCode()
{
    QString code =
    "int f()\n\
    {\
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
    qDebug() << "observe:" << _code;

}

void TestQHelpFunctionTest::test_qhGetEnumMap()
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

void TestQHelpFunctionTest::test_qhDomFindElement()
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

void TestQHelpFunctionTest::test_qhGetQSettingsXmlFormat()
{
    class SettingTextCodec
    {
    public:
        SettingTextCodec(QTextCodec *cl, QTextCodec *cs, QTextCodec *ct)
        {
            m_cl = QTextCodec::codecForLocale();
            m_cs = QTextCodec::codecForCStrings();
            m_ct = QTextCodec::codecForTr();

            QTextCodec::setCodecForLocale(cl);
            QTextCodec::setCodecForCStrings(cs);
            QTextCodec::setCodecForTr(ct);
        }

        ~SettingTextCodec()
        {
            QTextCodec::setCodecForLocale(m_cl);
            QTextCodec::setCodecForCStrings(m_cs);
            QTextCodec::setCodecForTr(m_ct);
        }
    private:
        QTextCodec *m_cl;
        QTextCodec *m_cs;
        QTextCodec *m_ct;
    };

    QTextCodec * codec = QTextCodec::codecForName("GBK");
    SettingTextCodec stc(codec, codec, codec);

    {
        QFile::remove(tr("../TestQHelpFunction/QSettingsXmlFormatTestTmp.xml"));
        QVERIFY( QFile::copy(tr("../TestQHelpFunction/QSettingsXmlFormatTest.xml"),
                             tr("../TestQHelpFunction/QSettingsXmlFormatTestTmp.xml")) );
        EQHEncode encode = EQHEncodeUTF8;
        QSettings::Format xmlformat = qhGetQSettingsXmlFormat(encode);
        QVERIFY(xmlformat != QSettings::IniFormat);
        QSettings s("../TestQHelpFunction/QSettingsXmlFormatTestTmp.xml", xmlformat);

        QStringList keys = s.allKeys();
        QVERIFY(keys.size() == 6);
        QStringList groups = s.childGroups ();
        QVERIFY(groups.size() == 1);
        keys = s.childKeys ();
        QVERIFY(keys.size() == 0);
        s.beginGroup("dido_config_table");
        keys = s.childKeys ();
        QVERIFY(keys.size() == 1);
        s.endGroup();

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
    }

    {
        QFile::remove(tr("../TestQHelpFunction/QSettingsXmlFormatTestTmp.xml"));
        QVERIFY( QFile::copy(tr("../TestQHelpFunction/QSettingsXmlFormatTest.xml"),
                             tr("../TestQHelpFunction/QSettingsXmlFormatTestTmp.xml")) );
        EQHEncode encode = EQHEncodeGBK;
        QSettings::Format xmlformat = qhGetQSettingsXmlFormat( encode);
        QVERIFY(xmlformat != QSettings::IniFormat);
        QSettings s("../TestQHelpFunction/QSettingsXmlFormatTestTmp.xml", xmlformat);

        QStringList keys = s.allKeys();
        QVERIFY(keys.size() == 6);
        QStringList groups = s.childGroups ();
        QVERIFY(groups.size() == 1);
        keys = s.childKeys ();
        QVERIFY(keys.size() == 0);
        s.beginGroup("dido_config_table");
        keys = s.childKeys ();
        QVERIFY(keys.size() == 1);
        s.endGroup();

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

        // 测试多次注册
        for(int i=0; i<100; i++)
            QVERIFY(qhGetQSettingsXmlFormat( encode) != QSettings::IniFormat);
    }

}

QTEST_MAIN(TestQHelpFunctionTest)

#include "tst_TestQHelpFunctionTest.moc"
