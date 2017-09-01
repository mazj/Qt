#include "testqssmainwnd.h"
#include "ui_testqssmainwnd.h"

TestQssMainWnd::TestQssMainWnd(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TestQssMainWnd)
{
    ui->setupUi(this);
}

TestQssMainWnd::~TestQssMainWnd()
{
    delete ui;
}
