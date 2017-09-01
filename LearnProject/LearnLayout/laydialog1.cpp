#include "LayDialog1.h"
#include "ui_laydialog1.h"

LayDialog1::LayDialog1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LayDialog1)
{
    ui->setupUi(this);
}

LayDialog1::~LayDialog1()
{
    delete ui;
}
