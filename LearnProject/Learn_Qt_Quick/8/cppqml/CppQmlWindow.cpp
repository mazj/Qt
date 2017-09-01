#include "CppQmlWindow.h"
#include "ui_CppQmlWindow.h"

CppQmlWindow::CppQmlWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CppQmlWindow)
{
    ui->setupUi(this);
}

CppQmlWindow::~CppQmlWindow()
{
    delete ui;
}
