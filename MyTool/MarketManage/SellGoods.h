#ifndef SELLGOODS_H
#define SELLGOODS_H

#include <QWidget>

namespace Ui {
class SellGoods;
}

class SellGoods : public QWidget
{
    Q_OBJECT

public:
    explicit SellGoods(QWidget *parent = 0);
    ~SellGoods();

private:
    Ui::SellGoods *ui;
};

#endif // SELLGOODS_H
