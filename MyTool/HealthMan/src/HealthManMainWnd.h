#ifndef HEALTHMANMAINWND_H
#define HEALTHMANMAINWND_H

#include <QDialog>
#include <QTime>

#include <QHTool/CornerPromptBox.h>

namespace Ui {
class Dialog;
}

class RemindUI;
class SystemTrayIcon;

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

protected:
    virtual void timerEvent(QTimerEvent *);
    virtual void closeEvent(QCloseEvent *);

public slots:
    //virtual void done(int);
    virtual void accept();
    virtual void reject();

    void slotDelay(int m);

private:
    void startRemindBegingAt(const QTime & beginTime);

private:
    Ui::Dialog *ui;
    QTime m_moringBeginTime;
    QTime m_afternoonBeginTime;
    QTime m_processRunTime;
    QTime m_nextRemindTime;

    int m_timerId;

    CornerPromptBox m_remindBox;
    RemindUI *m_pRemindUI;
    SystemTrayIcon *m_pSystemTrayIcon;
};

#endif // HEALTHMANMAINWND_H
