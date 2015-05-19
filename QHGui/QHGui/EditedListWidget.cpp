#include "EditedListWidget.h"
#include "ui_EditedListWidget.h"
#include "QHTool/qHelpFunction.h"

EditedListWidget::EditedListWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditedListWidget)
{
    ui->setupUi(this);
    // ֻѡһ��item
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->delButton->setEnabled(false);
}

EditedListWidget::~EditedListWidget()
{
    delete ui;
}

/**
 * ���һ�У������� name
 * @param name
 * @return
 */
QTableWidgetItem *EditedListWidget::addRow(const QString &name)
{
    int index = findSelectRow();
    ui->tableWidget->insertRow(++index);

    QTableWidgetItem *pItem = new QTableWidgetItem(name);
    ui->tableWidget->setItem(index, 0, pItem);

    emit sigAddedItem(pItem);

    QH_VERIFY( selectRow(index) );

    return pItem;
}

EditedListWidget& EditedListWidget::operator << (const QString &name)
{
    addRow(name);

    return *this;
}

EditedListWidget &EditedListWidget::operator <<(QStringList &ratioList)
{
    foreach (const QString & s, ratioList) {
        (*this) << s;
    }

    return *this;
}

/**
 * ��ȡÿһ�е�����
 * @param ratioList
 * @return
 */
EditedListWidget& EditedListWidget::operator >> (QStringList &ratioList)
{
    int count = ui->tableWidget->rowCount();

    for (int i=0; i<count; i++)
        ratioList << ui->tableWidget->item(i, 0)->text();

    return *this;
}

/**
 * ѡ�� �� row
 * @param row
 * @return
 */
bool EditedListWidget::selectRow(int row)
{
    // ����ѡ��ÿһ�� item �� Ϊ�˽������� ��ʾֻ��һ�� item ��ѡ�У������� qt��bug
    QList<QTableWidgetItem *> list = ui->tableWidget->selectedItems();
    foreach (QTableWidgetItem *item, list) {
        item->setSelected(false);
    }

    QTableWidgetItem *item = ui->tableWidget->item(row, 0);
    if (item)
    {
        item->setSelected(true); 
        ui->delButton->setEnabled(true);
        return true;
    }
    else
    {
        ui->delButton->setEnabled(false);
        return false;
    }
}

/**
 * ɾ��������
 */
void EditedListWidget::clear()
{
    while(ui->tableWidget->rowCount() != 0)
        ui->tableWidget->removeRow(0);

    ui->delButton->setEnabled(false);
}

/**
 * ����� ��Ӱ����� selectedItems����ѡ��� item�������� currentItem �� activeItem
 * ��֪����ôʹ�ã����ﲻʹ��.
 * ���� EditedListWidget ��ֻʹ�� selectedItems
 * @return
 */
int EditedListWidget::findSelectRow()
{
    QList<QTableWidgetItem *> itemList = ui->tableWidget->selectedItems();
    int index;

    if (!itemList.empty())
    {
        index = ui->tableWidget->row(itemList.first());
    }
    else if (ui->tableWidget->rowCount() <= 0)
    {
        index = -1;
    }
    else
    {
        Q_ASSERT(0);
    }

    return index;
}


void EditedListWidget::on_addButton_clicked()
{
    addRow(m_defaultItemStr);
}

void EditedListWidget::on_delButton_clicked()
{
    QList<QTableWidgetItem *> itemList = ui->tableWidget->selectedItems();
    int index = -1;
    QTableWidgetItem *item = NULL;

    if (!itemList.empty())
    {
        item = itemList.first();
        index = ui->tableWidget->row(item);
        emit sigDeletedItem(item);
        ui->tableWidget->removeRow(index);
        if ( index < ui->tableWidget->rowCount() )
        {
            QH_VERIFY( selectRow( index ) );
        }
        else
        {
            selectRow( index-1 );
        }
    }

}

void EditedListWidget::on_tableWidget_itemSelectionChanged()
{
    QList<QTableWidgetItem*> list = ui->tableWidget->selectedItems();
    QString str;
    QTableWidgetItem *item = NULL;

    if (!list.empty())
    {
        str = list.first()->text();
        item = list.first();
    }
    emit sigSelectedItem(item);
    //emit sigSelected(str);    //ûѡ��ľͷ����մ�
}
