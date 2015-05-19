#ifndef REMINDUI_H
#define REMINDUI_H

#include <QWidget>

namespace Ui {
class RemindUI;
}

class RemindUI : public QWidget
{
    Q_OBJECT

public:
    explicit RemindUI(QWidget *parent = 0);
    ~RemindUI();

private slots:
    void on_delayPushButton_clicked();
    void on_delayPushButton_2_clicked();

    void on_delayPushButton_3_clicked();

    void on_delaypushButton_4_clicked();

signals:
    void sigDelay(int m);
private:
    Ui::RemindUI *ui;
};

#endif // REMINDUI_H
