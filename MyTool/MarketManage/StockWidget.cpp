#include "StockWidget.h"
#include "ui_StockWidget.h"

StockWidget::StockWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StockWidget)
{
    ui->setupUi(this);
}

StockWidget::~StockWidget()
{
    delete ui;
}
