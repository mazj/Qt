#ifndef QTABLEMAINWND_H
#define QTABLEMAINWND_H

#include <QMainWindow>

namespace Ui {
class QTableMainWnd;
}

class QTableMainWnd : public QMainWindow
{
    Q_OBJECT

public:
    explicit QTableMainWnd(QWidget *parent = 0);
    ~QTableMainWnd();

private:
    Ui::QTableMainWnd *ui;
};

#endif // QTABLEMAINWND_H
