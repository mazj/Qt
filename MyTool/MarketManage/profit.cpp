#include "profit.h"
#include "ui_profit.h"

Profit::Profit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Profit)
{
    ui->setupUi(this);
}

Profit::~Profit()
{
    delete ui;
}
