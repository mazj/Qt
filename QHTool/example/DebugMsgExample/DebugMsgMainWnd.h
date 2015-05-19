#ifndef DEBUGMSGMAINWND_H
#define DEBUGMSGMAINWND_H

#include <QMainWindow>

namespace Ui {
class DebugMsgMainWnd;
}

class DebugMsgMainWnd : public QMainWindow
{
    Q_OBJECT

public:
    explicit DebugMsgMainWnd(QWidget *parent = 0);
    ~DebugMsgMainWnd();
    void subFunc();
private:
    Ui::DebugMsgMainWnd *ui;
};

#endif // DEBUGMSGMAINWND_H
