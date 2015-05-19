#include "ListwidgetMainWnd.h"
#include "ui_ListwidgetMainWnd.h"
#include <QHBoxLayout>
#include <QListWidget>
#include "ListWidget.h"

#include <QHTool/HelpObject.h>



ListwidgetMainWnd::ListwidgetMainWnd(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ListwidgetMainWnd),
    mNum(0),
    mTimerId(-1)
{
    ui->setupUi(this);

    QHBoxLayout *pLayout = new QHBoxLayout();
    ui->widget->setLayout(pLayout);

#ifdef OWN_LIST
#else
    mpListWidget = new QListWidget();
//    mpListWidget = new ListWidget();
    pLayout->addWidget(mpListWidget);
    for(mNum=0; mNum<20000; mNum++)
        mpListWidget->addItem(QString::number(mNum));

//	mpListWidget->_update();
#endif

}

ListwidgetMainWnd::~ListwidgetMainWnd()
{
    delete ui;
}

void ListwidgetMainWnd::on_pushButtonAddItem_clicked()
{
#ifdef OWN_LIST
#else
    mpListWidget->addItem(QString::number(++mNum));
#endif
    HelpObject::_dumpObjectTree(this);
}

void ListwidgetMainWnd::on_pushButtonstartTimer_clicked()
{
    mTimerId = startTimer(1000);
}

void ListwidgetMainWnd::on_pushButtonstopTimer_clicked()
{
    killTimer(mTimerId);
}

void ListwidgetMainWnd::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == mTimerId)
    {
#ifdef OWN_LIST
#else
//        mpListWidget->addItem(QString::number(++mNum));
        int n = mNum+100;
        for(; mNum<n; mNum++)
            mpListWidget->addItem(QString::number(++mNum));
#endif

    }
}
