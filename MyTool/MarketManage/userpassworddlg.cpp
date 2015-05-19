#include "userpassworddlg.h"
#include "ui_userpassworddlg.h"

#include "global.h"

UserPassWordDlg::UserPassWordDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserPassWordDlg)
{
    ui->setupUi(this);
}

UserPassWordDlg::~UserPassWordDlg()
{
    delete ui;
}

void UserPassWordDlg::on_pushButtonLogin_clicked()
{
    QString userName(ui->lineEditUser->text());
    QString password(ui->lineEditPassword->text());

    if (userName == tr("root")
            && password == tr("123456"))
    {
        g_g.m_bIsManage = true;
        g_g.m_userName = userName;
        accept();
    }
    else
    {
        g_g.m_bIsManage = false;
        g_g.m_userName = userName;
        accept();
    }
}

void UserPassWordDlg::on_pushButtonExit_clicked()
{
    reject();
}
