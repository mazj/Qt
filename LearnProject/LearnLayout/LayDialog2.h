#ifndef LAYDIALOG2_H
#define LAYDIALOG2_H

#include <QDialog>

namespace Ui {
class LayDialog2;
}

class LayDialog2 : public QDialog
{
    Q_OBJECT

public:
    explicit LayDialog2(QWidget *parent = 0);
    ~LayDialog2();

private:
    Ui::LayDialog2 *ui;
};

#endif // LAYDIALOG2_H
