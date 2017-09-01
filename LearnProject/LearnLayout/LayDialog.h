#ifndef LAYDIALOG_H
#define LAYDIALOG_H

#include <QDialog>

namespace Ui {
class LayDialog;
}

class LayDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LayDialog(QWidget *parent = 0);
    ~LayDialog();

private:
    Ui::LayDialog *ui;
};

#endif // LAYDIALOG_H
