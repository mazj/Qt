#include "SysMaintainWidget.h"
#include "ui_SysMaintainWidget.h"

SysMaintainWidget::SysMaintainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SysMaintainWidget)
{
    ui->setupUi(this);
}

SysMaintainWidget::~SysMaintainWidget()
{
    delete ui;
}
