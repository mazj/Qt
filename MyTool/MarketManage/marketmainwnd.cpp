#include "marketmainwnd.h"
#include "ui_marketmainwnd.h"

#include "global.h"

MarketMainWnd::MarketMainWnd(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MarketMainWnd)
{
    ui->setupUi(this);

    if (!g_g.m_bIsManage)
    {
        ui->pushButtonManageMan->setEnabled(false);
        ui->pushButtonProfit->setEnabled(false);
        ui->pushButtonManageSystem->setEnabled(false);
    }

    ui->stackedWidget->setCurrentWidget(ui->pageMain);
}

MarketMainWnd::~MarketMainWnd()
{
    delete ui;
}


void MarketMainWnd::on_pushButtonSell_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageMain_2);
    ui->stackedWidget_2->setCurrentWidget(ui->pageSell);
}

void MarketMainWnd::on_pushButtonInGoods_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageMain_2);
    ui->stackedWidget_2->setCurrentWidget(ui->pageInGoods);
}

void MarketMainWnd::on_pushButtonStock_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageMain_2);
    ui->stackedWidget_2->setCurrentWidget(ui->pageStock);
}

void MarketMainWnd::on_pushButtonManageMan_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageMain_2);
    ui->stackedWidget_2->setCurrentWidget(ui->pagePersonnelManage);
}

void MarketMainWnd::on_pushButtonProfit_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageMain_2);
    ui->stackedWidget_2->setCurrentWidget(ui->pageProfit);
}

void MarketMainWnd::on_pushButtonManageSystem_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageMain_2);
    ui->stackedWidget_2->setCurrentWidget(ui->pageSysMaintainWidget);
}

void MarketMainWnd::on_toolButtonMainPage_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageMain);
}
