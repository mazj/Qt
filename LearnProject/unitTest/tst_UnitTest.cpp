/**
    示例 qt 的单元测试的使用
  */

#include <QString>
#include <QtTest>
#include <QtGui>

// 定义单元测试类，继承 QObject， manual 上一个单元测试只用一个类，不知能不能定义多个
class UnitTest : public QObject
{
    Q_OBJECT
    
public:
    UnitTest();
    
// 每个private slot函数都是会被自动调用的测试函数
private Q_SLOTS:
//    initTestCase()：在测试开始前被调用
//    cleanupTestCase()：在测试结束后被调用
//    init()：每个测试函数执行前被调用
//    cleanup()：每个测试函数执行后被调用
    void initTestCase();    //初始化该单元测试
    void cleanupTestCase(); //清理该单元测试
#if 1
    void testCase1();   //测试1
    void testCase2();   //测试2
    void testPerformance(); // 性能测试
    void testPerformance1();

    //带数据的测试， func 会用 func_data函数提供的数据去测试
    void toUpper();
    void toUpper_data();

#endif
    // 也可以测试 图形界面控件
    void testGui();

    // 也可以以不同的数据测试 图形界面控件
    void testGui1_data();
    void testGui1();
};



UnitTest::UnitTest()
{
}

void UnitTest::initTestCase()
{
}

void UnitTest::cleanupTestCase()
{
}

#if 1
void UnitTest::testCase1()
{
    //主要的测试宏
    //QVERIFY检测表达式是否为真，
    //QCOMPARE 比较两个参数是否相等
    QVERIFY(0);  //若有测试失败，则剩下的测试代码不会再被执行了， 可以通过 QEXPECT_FAIL 设置
    QVERIFY2(0, "Failure");
}

void UnitTest::testCase2()
{
    QCOMPARE(3, 1+2);
    QVERIFY(true);
    QVERIFY2(true, "Failure testCase2");
    //qDebug() << __LINE__;
}

void UnitTest::testPerformance()
{
     QString str1 = QLatin1String("This is a test string");
     QString str2 = QLatin1String("This is a test string");

     QCOMPARE(str1.localeAwareCompare(str2), 0);
     //str1.localeAwareCompare(str2);
    //QThread::usleep(200);
     //qDebug() << __LINE__;
     // 性能测试 是测试 QBENCHMARK 块 或 QBENCHMARK_ONCE快内 代码的执行性能
     // QBENCHMARK 块内的代码 是通过多次运行获得平均时间的
     // QBENCHMARK_ONCE块内的只运行一次计算时间
     // 因为统计时间是以测试用例为单位的，所以一个测试用例我认为只能有一个 QBENCHMARK块或 一个
     // QBENCHMARK_ONCE块,不能有多个
     // 至于 包含 QBENCHMARK 或 QBENCHMARK_ONCE的函数会执行几次，qt文档中没有说明，我测试发现执行不止一次
     QBENCHMARK
     {
         //QCOMPARE(str1.localeAwareCompare(str2+"1"), 0);
         str1.localeAwareCompare(str2);
//         str1.localeAwareCompare(str2);
         //qDebug() << __LINE__;
     }

//     QBENCHMARK
//     {
//         //QCOMPARE(str1.localeAwareCompare(str2+"1"), 0);
//         str1.localeAwareCompare(str2);
//         qDebug() << __LINE__;
//     }

}


void UnitTest::testPerformance1()
{
//    qDebug() << __LINE__;
     QString str1 = QLatin1String("This is a test string");
     QString str2 = QLatin1String("This is a test string");

     QCOMPARE(str1.localeAwareCompare(str2), 0);

     QBENCHMARK
     {
         str1.compare(str2);
     }
}

// _data 函数 为 对应的测试用例提供数据，这里是为 toUpper 提供测试数据
void UnitTest::toUpper_data()
{
    // 数据的组织形式是二维表格，

    // 依次添加列, 数据类型必须是，元数据类型
    QTest::addColumn<QString>("string");  // 第一列
    QTest::addColumn<QString>("result");  // 第二列
    // 。。。依次添加列

    // 添加每行数据                  第一列数据   第二列数据， 数据是元数据类型就可以，基本数据类型也可以
    QTest::newRow("all lower")  << "hello" << "HELLO";// 第一行
    QTest::newRow("mixed")      << "hELLo" << "HELLO";// 第二行
    QTest::newRow("all upper")  << "HELLO" << "HELLO";// 第三行
    // 。。。依次添加每行数据

    //注： newRow（）的参数是每行数据的名称，用来区别不同的行
}

//有几行数据这个函数就会被调用几次
void UnitTest::toUpper()
{
    // 依次获取每列的数据
    QFETCH(QString, string); // 第一列
    QFETCH(QString, result); // 第二列

    QCOMPARE(string.toUpper(), result);

    // 一个 QFETCH 和 QCOMPARE 组合起来的快捷操作，暂时不用搞懂
    //QTEST(QString("hello").toUpper(), "myString");
}
#endif

void UnitTest::testGui()
{
    QLineEdit lineEdit;

    // 测试图形用户界面的原理是 qtestlib 模拟一些 用户事件，下面的函数模拟 在 lineEdit获得焦点是键盘敲击
    // hello world
    QTest::keyClicks(&lineEdit, "hello world");

    QCOMPARE(lineEdit.text(), QString("hello world"));
}

//具体解释见manual的 Home Examples Chapter 4: Replaying GUI Events
void UnitTest::testGui1_data()
{
    QTest::addColumn<QTestEventList>("events");
    QTest::addColumn<QString>("expected");

    QTestEventList list;
    list.addKeyClick('a');
    QTest::newRow("char") << list << "a";

    QTestEventList list2;
    list2.addKeyClick('a');
    list2.addKeyClick(Qt::Key_Backspace);

    QTest::newRow("there and back again") << list2 << "rr";
}

void UnitTest::testGui1()
{
    // QSKIP 用来跳过测试用例，
    // 对于数据测试 QTest::SkipAll跳过所有该测试用例的数据行， SkipSingle只跳过一行数据测试
    //QSKIP("skip this", SkipAll);

    QFETCH(QTestEventList, events);
    QFETCH(QString, expected);

    QLineEdit lineEdit;
    events.simulate(&lineEdit);

    QCOMPARE(lineEdit.text(), expected);
}

#if 0
// 用于构建可执行的测试程序
//QTEST_APPLESS_MAIN(UnitTest)
QTEST_MAIN(UnitTest)
#elif 1
class UnitTest1 : public QObject
{
    Q_OBJECT
public:
    UnitTest1() {}
    virtual ~UnitTest1() {}

private Q_SLOTS:
    void testCase1()
    {
        QVERIFY2(0, "Failure");
    }
};

// 这么做倒是可以在同一个 程序中运行多个单元测试，但感觉还不是很好，因为每个单元测试的命令行参数可能是不同的，
// 而且不能统计有多少个单元测试 通过了
// 可以自己写测试主函数，可以有多个测试类， 运行多次 QTest::qExec
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    UnitTest tc;
    QTest::qExec(&tc, argc, argv);

    UnitTest1 tc1;
    QTest::qExec(&tc1, argc, argv);
}
#endif

#include "tst_UnitTest.moc"
