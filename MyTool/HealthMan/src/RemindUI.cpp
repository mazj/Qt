#include "RemindUI.h"
#include "ui_RemindUI.h"

#include <QDebug>

RemindUI::RemindUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RemindUI)
{
    ui->setupUi(this);
}

RemindUI::~RemindUI()
{
    delete ui;
}

void RemindUI::on_delayPushButton_clicked()
{
    emit sigDelay(5);
}

void RemindUI::on_delayPushButton_2_clicked()
{
    emit sigDelay(10);
}

void RemindUI::on_delayPushButton_3_clicked()
{
    emit sigDelay(15);
}

void RemindUI::on_delaypushButton_4_clicked()
{
    int minute = ui->spinBox->value();
    qDebug() << "ui->spinBox->value() = " << minute;
    emit sigDelay(minute);
}
