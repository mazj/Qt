#ifndef QHTOOLTEST_H
#define QHTOOLTEST_H

#include <QObject>

class QHToolTest : public QObject
{
    Q_OBJECT

public:
    QHToolTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

    void test_qhQStringFindLineEndPos();
    void test_qhRemoveExegesisInCode();
    void test_qhGetEnumMap();

    void test_qhIsQSettingsXmlFormatFile();
    void test_HelpQChar();
    void test_HelpQString();
    void test_HelpQFile();
    void test_convertCCodeString();
    void test_uniqueQList();
    void test_qhQListReplace();
    void test_qhDomFindElement();
    void test_qhGetQSettingsXmlFormat_data();
    void test_qhGetQSettingsXmlFormat();

    //暂时不测试的项目
private:

};



#endif // QHTOOLTEST_H
