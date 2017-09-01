#ifndef CPPQMLWINDOW_H
#define CPPQMLWINDOW_H

#include <QMainWindow>

namespace Ui {
class CppQmlWindow;
}

class CppQmlWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CppQmlWindow(QWidget *parent = 0);
    ~CppQmlWindow();

private:
    Ui::CppQmlWindow *ui;
};

#endif // CPPQMLWINDOW_H
