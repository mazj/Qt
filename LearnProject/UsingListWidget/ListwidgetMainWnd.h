#ifndef LISTWIDGETMAINWND_H
#define LISTWIDGETMAINWND_H

#include <QMainWindow>

//#define OWN_LIST

namespace Ui {
class ListwidgetMainWnd;
}
class QTimerEvent;
class QListWidget;
class ListWidget;
class ListwidgetMainWnd : public QMainWindow
{
    Q_OBJECT

public:
    explicit ListwidgetMainWnd(QWidget *parent = 0);
    ~ListwidgetMainWnd();

private slots:
    void on_pushButtonAddItem_clicked();

    void on_pushButtonstartTimer_clicked();

    void on_pushButtonstopTimer_clicked();

    void timerEvent(QTimerEvent * event);

private:
    Ui::ListwidgetMainWnd *ui;
    int mNum;
    int mTimerId;
#ifdef OWN_LIST
#else
    QListWidget *mpListWidget;
    //ListWidget *mpListWidget;
#endif
};

#endif // LISTWIDGETMAINWND_H
