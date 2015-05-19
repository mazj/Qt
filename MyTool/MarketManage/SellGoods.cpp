#include "SellGoods.h"
#include "ui_SellGoods.h"

SellGoods::SellGoods(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SellGoods)
{
    ui->setupUi(this);
}

SellGoods::~SellGoods()
{
    delete ui;
}
