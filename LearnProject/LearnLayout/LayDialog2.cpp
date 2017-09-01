#include "LayDialog2.h"
#include "ui_LayDialog2.h"

LayDialog2::LayDialog2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LayDialog2)
{
    ui->setupUi(this);
}

LayDialog2::~LayDialog2()
{
    delete ui;
}
