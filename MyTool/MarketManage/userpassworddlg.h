#ifndef USERPASSWORDDLG_H
#define USERPASSWORDDLG_H

#include <QDialog>

namespace Ui {
class UserPassWordDlg;
}

class UserPassWordDlg : public QDialog
{
    Q_OBJECT

public:
    explicit UserPassWordDlg(QWidget *parent = 0);
    ~UserPassWordDlg();

private slots:
    void on_pushButtonLogin_clicked();

    void on_pushButtonExit_clicked();

private:
    Ui::UserPassWordDlg *ui;
};

#endif // USERPASSWORDDLG_H
