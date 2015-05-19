#include "PersonnelManage.h"
#include "ui_PersonnelManage.h"

PersonnelManage::PersonnelManage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PersonnelManage)
{
    ui->setupUi(this);

}

PersonnelManage::~PersonnelManage()
{
    delete ui;
}
