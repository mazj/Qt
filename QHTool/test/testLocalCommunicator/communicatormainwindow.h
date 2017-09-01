#ifndef COMMUNICATORMAINWINDOW_H
#define COMMUNICATORMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class CommunicatorMainWindow;
}

class CommunicatorMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CommunicatorMainWindow(QWidget *parent = 0);
    ~CommunicatorMainWindow();

private:
    Ui::CommunicatorMainWindow *ui;
};

#endif // COMMUNICATORMAINWINDOW_H
