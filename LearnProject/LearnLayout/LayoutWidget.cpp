#include "LayoutWidget.h"
#include "ui_LayoutWidget.h"

LayoutWidget::LayoutWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayoutWidget)
{
    ui->setupUi(this);
}

LayoutWidget::~LayoutWidget()
{
    delete ui;
}
