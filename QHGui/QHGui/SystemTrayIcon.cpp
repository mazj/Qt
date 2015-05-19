#include "SystemTrayIcon.h"

#include <QMenu>
#include <QSystemTrayIcon>
#include <QApplication>


/**
 * @brief SystemTrayIcon::SystemTrayIcon
 * @param pWindow Ӧ�ó���������
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
    QAction *miniSizeAction = new QAction(tr("��С��(&N)"),this);
    QAction *maxSizeAction = new QAction(tr("���(&X)"),this);
    QAction *restoreWinAction = new QAction(tr("�� ԭ(&R)"),this);
    QAction *quitAction = new QAction(tr("�˳�(&Q)"),this);

    this->connect(miniSizeAction, SIGNAL(triggered()),m_pWindow, SLOT(hide()));
    this->connect(maxSizeAction, SIGNAL(triggered()), m_pWindow, SLOT(showMaximized()));
    this->connect(restoreWinAction,SIGNAL(triggered()),m_pWindow, SLOT(showNormal()));
    this->connect(quitAction,SIGNAL(triggered()),qApp, SLOT(quit()));

    m_pMenu = new QMenu((QWidget*)QApplication::desktop());

    m_pMenu->addAction(miniSizeAction);
    m_pMenu->addAction(maxSizeAction);
    m_pMenu->addAction(restoreWinAction);
    m_pMenu->addSeparator();     //����һ�������
    m_pMenu->addAction(quitAction);
}

void SystemTrayIcon::creatTrayIcon()
{
    creatTrayMenu();

    if (!QSystemTrayIcon::isSystemTrayAvailable())      //�ж�ϵͳ�Ƿ�֧��ϵͳ����ͼ��
    {
        return;
    }

//48.    myTrayIcon = new QSystemTrayIcon(this);
//49.
//50.    myTrayIcon->setIcon(QIcon("mytrayIcon.ico"));   //����ͼ��ͼƬ
//51.    setWindowIcon(QIcon("mytrayIcon.ico"));  //��ͼƬ���õ�������
//52.
//53.    myTrayIcon->setToolTip("SystemTrayIcon V1.0");    //����ʱ��������ȥ����ʾ��Ϣ
//54.
//55.    myTrayIcon->showMessage("SystemTrayIcon","Hi,This is my trayIcon",QSystemTrayIcon::Information,10000);
//56.
//57.
//58.
    setContextMenu(m_pMenu);     //�������������Ĳ˵�

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
                m_pWindow->showNormal();    // ��ʱ�򴰿ڲ���ʾ�����ϲ������ϣ����ܻᱻ��Ĵ��ڵ�ס����ʱ�������
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
