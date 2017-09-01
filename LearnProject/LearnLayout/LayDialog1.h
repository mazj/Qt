#ifndef LAYDIALOG1_H
#define LAYDIALOG1_H

#include <QDialog>

namespace Ui {
class LayDialog1;
}

class LayDialog1 : public QDialog
{
    Q_OBJECT

public:
    explicit LayDialog1(QWidget *parent = 0);
    ~LayDialog1();

private:
    Ui::LayDialog1 *ui;
};

#endif // LAYDIALOG1_H
