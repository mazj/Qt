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

    // QTableWidget �ı�ͷ�����޷����У����뵽һ������������� �ѱ�ͷ���أ��õ�һ�л��һ������ͷ��
    // Ȼ��ѵ�һ�� ���һ�е� widget ���ó� QLabel����Ϊ label �ǿ�����ʾ���ı��ģ����Կ����ı���ʽ
    QLabel *pLabel = new QLabel(QString::fromLocal8Bit("��һ����<br>�ڶ�����"));
    ui->tableWidget_2->setCellWidget(0, 1, pLabel);
}

QTableMainWnd::~QTableMainWnd()
{
    delete ui;
}
