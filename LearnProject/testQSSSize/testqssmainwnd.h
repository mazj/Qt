#ifndef TESTQSSMAINWND_H
#define TESTQSSMAINWND_H

#include <QMainWindow>

namespace Ui {
class TestQssMainWnd;
}

class TestQssMainWnd : public QMainWindow
{
    Q_OBJECT

public:
    explicit TestQssMainWnd(QWidget *parent = 0);
    ~TestQssMainWnd();

private:
    Ui::TestQssMainWnd *ui;
};

#endif // TESTQSSMAINWND_H
