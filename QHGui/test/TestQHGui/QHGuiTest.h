#ifndef QHGUITEST_H
#define QHGUITEST_H

#include <QObject>

class QHGuiTest : public QObject
{
    Q_OBJECT
public:
    explicit QHGuiTest(QObject *parent = 0);

signals:

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void test_qhFindStrInComboBox();
    void test_qhGetComboBoxAllItemtext();
//    qhSetComboBoxValue()  //

    // QTableWidget
    void test_qhGetQTableWidgetAllItem();

};

#endif // QHGUITEST_H
