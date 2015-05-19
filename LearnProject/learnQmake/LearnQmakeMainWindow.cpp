#include "LearnQmakeMainWindow.h"
#include "ui_LearnQmakeMainWindow.h"

LearnQmakeMainWindow::LearnQmakeMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LearnQmakeMainWindow)
{
    ui->setupUi(this);
}

LearnQmakeMainWindow::~LearnQmakeMainWindow()
{
    delete ui;
}
