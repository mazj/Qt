#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "../MyPlugin/IMyPlugin.h"

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

private:
    bool loadPlugin();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWidget *ui;
    IMyPlugin   *mpPlugin;

    static int ms_num;
};

#endif // MAINWIDGET_H
