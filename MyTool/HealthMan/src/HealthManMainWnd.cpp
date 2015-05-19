#include "HealthManMainWnd.h"
#include "ui_HealthManMainWnd.h"

#include "inc.h"
#include <QCloseEvent>
#include <QPushButton>
#include <QHTool/CornerPromptBox.h>
#include <QHTool/SystemTrayIcon.h>

#include "RemindUI.h"




Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog),
    m_moringBeginTime(8, 30),
    m_afternoonBeginTime(12, 45),
    m_processRunTime(QTime::currentTime()),
    m_timerId(0)
{
    ui->setupUi(this);
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setDefault(true);

    m_remindBox.setFixedSize(600, 400);
    m_remindBox.setUseAnimation(true);
    m_remindBox.setWindowTitle(tr("健康人提醒！"));

   m_pRemindUI = new RemindUI();
   connect(m_pRemindUI, SIGNAL(sigDelay(int)), this, SLOT(slotDelay(int)));


   QIcon ic("://picture/health.ico");
   setWindowIcon(ic);

   m_pSystemTrayIcon = new SystemTrayIcon(this);
   m_pSystemTrayIcon->setIcon(ic);
   m_pSystemTrayIcon->setToolTip(tr("争做健康it人"));    //托盘时，鼠标放上去的提示信息
   m_pSystemTrayIcon->show();
//   if (pSystemTrayIcon->supportsMessages())
//       pSystemTrayIcon->showMessage("SystemTrayIcon","Hi,This is my trayIcon",QSystemTrayIcon::Information,10000);

   startRemindBegingAt(m_processRunTime);
   m_timerId = startTimer(1000);
}

Dialog::~Dialog()
{
    delete ui;
    m_pRemindUI->deleteLater();
}

void Dialog::timerEvent(QTimerEvent *e)
{
    if (e->timerId() == m_timerId)
    {
        //killTimer(m_timerId);

//        QFont f;
//        f.setPointSize(30);
//        m_remindBox.setContent(tr("主人，该让你的腰部休息 5 分钟了哦！！"), &f);
        QTime now = QTime::currentTime();
        QTime t;
        if (now >= m_nextRemindTime)
        {
            m_remindBox.setContent(m_pRemindUI);
            m_remindBox.showMsg(1000 * 60 * 5);
            m_remindBox.clearFocus();
			m_nextRemindTime = now.addSecs(INTERVAL_BY_MINUTE*60);
            t = t.addSecs(INTERVAL_BY_MINUTE*60);
            ui->lcdNumber->display(t.toString("hh:mm:ss"));
            //ui->timeEdit->setTime(t);
        }
        else
        {
            t = t.addSecs(now.secsTo(m_nextRemindTime));
            ui->lcdNumber->display(t.toString("hh:mm:ss"));
//            ui->timeEdit->setTime( t);
        }

        //m_timerId = startTimer(INTERVAL_BY_MINUTE * 60 * 1000);
    }
    else
    {
        return QDialog::timerEvent(e);
    }
}

void Dialog::closeEvent(QCloseEvent *e)
{
     e->accept();
     //hide();
}

void Dialog::accept()
{
    // 以固定时间模式运行
    if (ui->fixTimeRadioButton->isChecked())
    {
        QTime now(QTime::currentTime());
        if (now < m_afternoonBeginTime)
            startRemindBegingAt(m_moringBeginTime);
        else
            startRemindBegingAt(m_afternoonBeginTime);
    }

    // 以程序开始运行时间计时
    else if (ui->processRunTimeRadioButton->isChecked())
    {
        startRemindBegingAt(m_processRunTime);
    }

    //  以现在开始计时
    else if (ui->nowRadioButton->isChecked())
    {
        startRemindBegingAt(QTime::currentTime());
    }
    //hide();
    showMinimized();
    //QDialog::accept();
}

void Dialog::reject()
{
    //hide();
    showMinimized();
    //QDialog::reject();
}

void Dialog::slotDelay(int m)
{
    Q_ASSERT(m > 0);
    //killTimer(m_timerId);
    //m_timerId = startTimer(m * 60 * 1000);
    m_nextRemindTime = QTime::currentTime().addSecs(m * 60);
    QTime t;
    t = t.addSecs(m * 60);
    ui->lcdNumber->display(t.toString("hh:mm:ss"));
//    ui->timeEdit->setTime(t);
    m_remindBox.slotHideMsg();
}

/**
 * @brief 从　beginTime　开始经过　ｎ个固定时间后　提醒，提醒时间点　必须　在现在以后
 * @param beginTime
 */
void Dialog::startRemindBegingAt(const QTime &beginTime)
{
    QTime now = QTime::currentTime();
    QTime t;
    if (now <= beginTime)
    {
        m_nextRemindTime = beginTime.addSecs(INTERVAL_BY_MINUTE*60);
        //killTimer(m_timerId);
        //m_timerId = startTimerAtTime(this, m_nextRemindTime);
        t = t.addSecs(INTERVAL_BY_MINUTE*60);
    }
    else
    {
        QTime nextTime = beginTime.addSecs(INTERVAL_BY_MINUTE*60);
        while(!(nextTime>=now))
        {
            nextTime = nextTime.addSecs(INTERVAL_BY_MINUTE*60);
        }
        m_nextRemindTime = nextTime;
        //killTimer(m_timerId);
        //m_timerId = startTimerAtTime(this, nextTime);

        t = t.addSecs(now.secsTo(m_nextRemindTime));
    }

//    ui->timeEdit->setTime(t);
    ui->lcdNumber->display(t.toString("hh:mm:ss"));
}
