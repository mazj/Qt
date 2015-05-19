#include "SystemTrayIcon.h"

#include <QMenu>
#include <QSystemTrayIcon>
#include <QApplication>


/**
 * @brief SystemTrayIcon::SystemTrayIcon
 * @param pWindow 应用程序主窗口
 */
SystemTrayIcon::SystemTrayIcon(QWidget *pWindow) :
    QSystemTrayIcon(pWindow),
    m_pWindow(pWindow)
{
//    CreatTrayMenu();
    creatTrayIcon();

//    void sigWindowHide();
    //connect(this, SIGNAL(sigWindowShowNormal()),m_pWindow, SLOT(showNormal()));
}

void SystemTrayIcon::creatTrayMenu()
{
    QAction *miniSizeAction = new QAction(tr("最小化(&N)"),this);
    QAction *maxSizeAction = new QAction(tr("最大化(&X)"),this);
    QAction *restoreWinAction = new QAction(tr("还 原(&R)"),this);
    QAction *quitAction = new QAction(tr("退出(&Q)"),this);

    this->connect(miniSizeAction, SIGNAL(triggered()),m_pWindow, SLOT(hide()));
    this->connect(maxSizeAction, SIGNAL(triggered()), m_pWindow, SLOT(showMaximized()));
    this->connect(restoreWinAction,SIGNAL(triggered()),m_pWindow, SLOT(showNormal()));
    this->connect(quitAction,SIGNAL(triggered()),qApp, SLOT(quit()));

    m_pMenu = new QMenu((QWidget*)QApplication::desktop());

    m_pMenu->addAction(miniSizeAction);
    m_pMenu->addAction(maxSizeAction);
    m_pMenu->addAction(restoreWinAction);
    m_pMenu->addSeparator();     //加入一个分离符
    m_pMenu->addAction(quitAction);
}

void SystemTrayIcon::creatTrayIcon()
{
    creatTrayMenu();

    if (!QSystemTrayIcon::isSystemTrayAvailable())      //判断系统是否支持系统托盘图标
    {
        return;
    }

//48.    myTrayIcon = new QSystemTrayIcon(this);
//49.
//50.    myTrayIcon->setIcon(QIcon("mytrayIcon.ico"));   //设置图标图片
//51.    setWindowIcon(QIcon("mytrayIcon.ico"));  //把图片设置到窗口上
//52.
//53.    myTrayIcon->setToolTip("SystemTrayIcon V1.0");    //托盘时，鼠标放上去的提示信息
//54.
//55.    myTrayIcon->showMessage("SystemTrayIcon","Hi,This is my trayIcon",QSystemTrayIcon::Information,10000);
//56.
//57.
//58.
    setContextMenu(m_pMenu);     //设置托盘上下文菜单

    //myTrayIcon->show();
    this->connect(this, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
                  this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
}

void SystemTrayIcon::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason)
    {
    case QSystemTrayIcon::Trigger:
        break;
    case QSystemTrayIcon::DoubleClick:
        {
            if (m_pWindow->isHidden() || m_pWindow->isMinimized())
            {
                m_pWindow->showNormal();    // 有时候窗口不显示在最上层桌面上，可能会被别的窗口挡住。暂时解决不了
               // m_pWindow->setWindowState(m_pWindow->windowState() | Qt::WindowActive);
                //m_pWindow->setWindowState(m_pWindow->windowState() & ~Qt::WindowMinimized | Qt::WindowActive);
            }
            else
            {
                m_pWindow->hide();
            }
        } break;
    case QSystemTrayIcon::MiddleClick:
        //showMessage("SystemTrayIcon","Hi,This is my trayIcon",QSystemTrayIcon::Information,10000);
       break;

    default:
        break;
    }
}
