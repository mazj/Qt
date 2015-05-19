#ifndef EDITEDLISTMAINWND_H
#define EDITEDLISTMAINWND_H

#include <QMainWindow>

class EditedListWidget;
class QTableWidgetItem;
namespace Ui {
class EditedListMainWnd;
}

class EditedListMainWnd : public QMainWindow
{
    Q_OBJECT

public:
    explicit EditedListMainWnd(QWidget *parent = 0);
    ~EditedListMainWnd();

private slots:
    void slotSelectedItem(const QTableWidgetItem *item);
    void slotAddedItem(const QTableWidgetItem *item);
    void slotDeletedItem(const QTableWidgetItem *item);

    void on_actionTest_Add_row_triggered();

    void on_actionTest_Add_rows_triggered();

    void on_actionTest_Get_rows_triggered();

    void on_actionTest_clear_triggered();

private:
    Ui::EditedListMainWnd *ui;
    EditedListWidget *m_pEditedListWidget;
    int nNum;
};

#endif // EDITEDLISTMAINWND_H
