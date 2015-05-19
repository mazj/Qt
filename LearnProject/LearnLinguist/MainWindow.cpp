#include "MainWindow.h"
#include "ui_MainWindow.h"

#include<QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString s1 = QObject::tr("my tr 1");
    QString s = QObject::tr("my tr 1");
    QString s2 = QObject::tr("my tr 2");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString s1 = QObject::tr("my tr 1");
    qDebug() << s1;
}
