#ifndef FIRSTLEVELMAINWND_H
#define FIRSTLEVELMAINWND_H

#include <QMainWindow>

namespace Ui {
class FirstLevelMainWnd;
}

class FirstLevelMainWnd : public QMainWindow
{
    Q_OBJECT

public:
    explicit FirstLevelMainWnd(QWidget *parent = 0);
    ~FirstLevelMainWnd();

private:
    Ui::FirstLevelMainWnd *ui;
};

#endif // FIRSTLEVELMAINWND_H
