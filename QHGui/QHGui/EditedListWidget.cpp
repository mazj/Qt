#include "EditedListWidget.h"
#include "ui_EditedListWidget.h"
#include "QHTool/qHelpFunction.h"

EditedListWidget::EditedListWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditedListWidget)
{
    ui->setupUi(this);
    // 只选一个item
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->delButton->setEnabled(false);
}

EditedListWidget::~EditedListWidget()
{
    delete ui;
}

/**
 * 添加一行，内容是 name
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
 * 获取每一行的内容
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
 * 选择 行 row
 * @param row
 * @return
 */
bool EditedListWidget::selectRow(int row)
{
    // 不再选择每一个 item 是 为了界面上能 显示只有一个 item 被选中，可能是 qt的bug
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
 * 删除所有行
 */
void EditedListWidget::clear()
{
    while(ui->tableWidget->rowCount() != 0)
        ui->tableWidget->removeRow(0);

    ui->delButton->setEnabled(false);
}

/**
 * 鼠标点击 会影响的是 selectedItems，即选择的 item。其他的 currentItem 或 activeItem
 * 不知道怎么使用，这里不使用.
 * 这里 EditedListWidget 都只使用 selectedItems
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
    //emit sigSelected(str);    //没选择的就发个空串
}
