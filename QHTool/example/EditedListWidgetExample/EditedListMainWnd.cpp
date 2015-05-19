#include "EditedListMainWnd.h"
#include "ui_EditedListMainWnd.h"
#include <QTableWidgetItem>
#include <QDebug>

#include "QHTool/EditedListWidget.h"


EditedListMainWnd::EditedListMainWnd(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EditedListMainWnd),
    nNum()
{
    ui->setupUi(this);

    m_pEditedListWidget = new EditedListWidget();
    m_pEditedListWidget->setDefaultItemStr("DefaultItemStr");

    // а╛╫спе╨е
    connect(m_pEditedListWidget, SIGNAL(sigSelectedItem(const QTableWidgetItem *)),
            SLOT(slotSelectedItem(const QTableWidgetItem*)));
    connect(m_pEditedListWidget, SIGNAL(sigAddedItem(const QTableWidgetItem*)),
            SLOT(slotAddedItem(const QTableWidgetItem*)) );
    connect(m_pEditedListWidget, SIGNAL(sigDeletedItem(const QTableWidgetItem *)),
            SLOT(slotDeletedItem(const QTableWidgetItem*)) );

    setCentralWidget(m_pEditedListWidget);
}

EditedListMainWnd::~EditedListMainWnd()
{
    delete ui;
}

void EditedListMainWnd::slotSelectedItem(const QTableWidgetItem *item)
{
    QString str = QString("SelectedItem ");

    if (item)
        str += item->text();
    else
        str += "item null";

    statusBar()->showMessage(str);
    qDebug() << str;
}

void EditedListMainWnd::slotAddedItem(const QTableWidgetItem *item)
{
    QString str = QString("slotAddedItem ");

    if (item)
        str += item->text();
    else
        str += "item null";

    statusBar()->showMessage(str);
    qDebug() << str;
}

void EditedListMainWnd::slotDeletedItem(const QTableWidgetItem *item)
{

    QString str = QString("slotDeletedItem ");

    if (item)
        str += item->text();
    else
        str += "item null";

    statusBar()->showMessage(str);
    qDebug() << str;
}

void EditedListMainWnd::on_actionTest_Add_row_triggered()
{
    m_pEditedListWidget->addRow(QString::number(nNum++));
}

void EditedListMainWnd::on_actionTest_Add_rows_triggered()
{
    QStringList l;
    l << QString::number(nNum++);
    l << QString::number(nNum++);
    l << QString::number(nNum++);

    (*m_pEditedListWidget) << l;
}

void EditedListMainWnd::on_actionTest_Get_rows_triggered()
{
    QStringList l;
    (*m_pEditedListWidget) >> l;

    qDebug() << l;
}

void EditedListMainWnd::on_actionTest_clear_triggered()
{
    m_pEditedListWidget->clear();
}
