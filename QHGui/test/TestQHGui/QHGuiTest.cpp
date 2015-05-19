#include <exception>
#include <algorithm>
#include <stdarg.h>
#include <assert.h>

#include <QString>
#include <QtTest>
#include <QCoreApplication>

#include <QtCore>
#include <QMap>
#include <QTableWidget>
#include <QComboBox>
#include <QRegExp>
#include <QStringList>

#include "QHGuiTest.h"
#include "QHGui/qhGui.h"

QHGuiTest::QHGuiTest(QObject *parent) :
    QObject(parent)
{
}

void QHGuiTest::initTestCase()
{
}

void QHGuiTest::cleanupTestCase()
{
}

void QHGuiTest::test_qhFindStrInComboBox()
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

void QHGuiTest::test_qhGetComboBoxAllItemtext()
{
    QComboBox com;
    QStringList l;
    l << QString("1") << QString("abc");
    l << QString(" ") << QString("abc") << QString("");
    com.addItems(l);

    QStringList l2;
    l2 = qhGetComboBoxAllItemtext(&com);

    QVERIFY(l == l2);
    QVERIFY(l2.size() == com.count());
    for(int i=0; i<com.count(); ++i)
    {
        QVERIFY(l2[i] == com.itemText(i));
    }
}

// empty
void QHGuiTest::test_qhGetQTableWidgetAllItem()
{
}
