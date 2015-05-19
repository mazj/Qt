#ifndef SYSMAINTAINWIDGET_H
#define SYSMAINTAINWIDGET_H

#include <QWidget>

namespace Ui {
class SysMaintainWidget;
}

class SysMaintainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SysMaintainWidget(QWidget *parent = 0);
    ~SysMaintainWidget();

private:
    Ui::SysMaintainWidget *ui;
};

#endif // SYSMAINTAINWIDGET_H
