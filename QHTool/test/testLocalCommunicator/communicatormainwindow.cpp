#include "communicatormainwindow.h"
#include "ui_communicatormainwindow.h"

CommunicatorMainWindow::CommunicatorMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CommunicatorMainWindow)
{
    ui->setupUi(this);
}

CommunicatorMainWindow::~CommunicatorMainWindow()
{
    delete ui;
}
