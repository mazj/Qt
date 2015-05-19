#include "FirstLevelMainWnd.h"
#include "ui_FirstLevelMainWnd.h"

FirstLevelMainWnd::FirstLevelMainWnd(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FirstLevelMainWnd)
{
    ui->setupUi(this);
}

FirstLevelMainWnd::~FirstLevelMainWnd()
{
    delete ui;
}
