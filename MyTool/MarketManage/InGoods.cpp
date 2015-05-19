#include "InGoods.h"
#include "ui_InGoods.h"

InGoods::InGoods(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InGoods)
{
    ui->setupUi(this);
}

InGoods::~InGoods()
{
    delete ui;
}
