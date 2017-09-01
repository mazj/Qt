#include "LayDialog.h"
#include "ui_LayDialog.h"

LayDialog::LayDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LayDialog)
{
    ui->setupUi(this);
}

LayDialog::~LayDialog()
{
    delete ui;
}
