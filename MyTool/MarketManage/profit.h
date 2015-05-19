#ifndef PROFIT_H
#define PROFIT_H

#include <QWidget>

namespace Ui {
class Profit;
}

class Profit : public QWidget
{
    Q_OBJECT

public:
    explicit Profit(QWidget *parent = 0);
    ~Profit();

private:
    Ui::Profit *ui;
};

#endif // PROFIT_H
