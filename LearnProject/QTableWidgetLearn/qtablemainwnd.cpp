#include "qtablemainwnd.h"
#include "ui_qtablemainwnd.h"

#include <QHeaderView>

#include <QLabel>

QTableMainWnd::QTableMainWnd(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QTableMainWnd)
{
    ui->setupUi(this);
    //QTableWidgetItem

    // QTableWidget 的表头文字无法换行，我想到一个替代方案就是 把表头隐藏，用第一行或第一列做表头。
    // 然后把第一行 或第一列的 widget 设置成 QLabel，因为 label 是可以显示富文本的，可以控制文本格式
    QLabel *pLabel = new QLabel(QString::fromLocal8Bit("第一行字<br>第二行字"));
    ui->tableWidget_2->setCellWidget(0, 1, pLabel);
}

QTableMainWnd::~QTableMainWnd()
{
    delete ui;
}
