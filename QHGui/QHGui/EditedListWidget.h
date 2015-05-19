#ifndef EDITEDLISTWIDGET_H
#define EDITEDLISTWIDGET_H

#include <QWidget>

class QTableWidgetItem;
namespace Ui {
class EditedListWidget;
}

/**
 * ʹ�� ���ɾ����ť����� ɾ��  QTableWidget��ÿ�У� QTableWidgetֻ��һ��
 */
class EditedListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EditedListWidget(QWidget *parent = 0);
    ~EditedListWidget();

    QTableWidgetItem *addRow(const QString &name);
    void setDefaultItemStr(const QString &str) { m_defaultItemStr = str;}
    EditedListWidget &operator <<(const QString &name);
    EditedListWidget &operator <<(QStringList &ratioList);
    EditedListWidget &operator >>(QStringList &ratioList);

    bool selectRow(int row);
    void clear();

signals:
    //void sigSelected(const QString & str);
    /**
     * ѡ���� item �ı���źţ�ÿ��ֻ��ѡ��һ�� item
     * @param item
     */
    void sigSelectedItem(const QTableWidgetItem *item);
    void sigAddedItem(const QTableWidgetItem *item);
    void sigDeletedItem(const QTableWidgetItem *item);

private:
    int findSelectRow();

private slots:
    void on_addButton_clicked();

    void on_delButton_clicked();

    void on_tableWidget_itemSelectionChanged();

private:
    Ui::EditedListWidget *ui;
    QString m_defaultItemStr;
};

#endif // EDITEDLISTWIDGET_H
