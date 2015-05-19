#ifndef MARKETMAINWND_H
#define MARKETMAINWND_H

#include <QMainWindow>

namespace Ui {
class MarketMainWnd;
}

class MarketMainWnd : public QMainWindow
{
    Q_OBJECT

public:
    explicit MarketMainWnd(QWidget *parent = 0);
    ~MarketMainWnd();

private slots:
    void on_pushButtonSell_clicked();

    void on_pushButtonInGoods_clicked();

    void on_pushButtonStock_clicked();

    void on_pushButtonManageMan_clicked();

    void on_pushButtonProfit_clicked();

    void on_pushButtonManageSystem_clicked();

    void on_toolButtonMainPage_clicked();

private:
    Ui::MarketMainWnd *ui;
};

#endif // MARKETMAINWND_H
