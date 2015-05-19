#ifndef INGOODS_H
#define INGOODS_H

#include <QWidget>

namespace Ui {
class InGoods;
}

class InGoods : public QWidget
{
    Q_OBJECT

public:
    explicit InGoods(QWidget *parent = 0);
    ~InGoods();

private:
    Ui::InGoods *ui;
};

#endif // INGOODS_H
