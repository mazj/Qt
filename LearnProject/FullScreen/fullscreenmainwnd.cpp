#include "fullscreenmainwnd.h"
#include "ui_fullscreenmainwnd.h"

#include <QDebug>


FullScreenMainWnd::FullScreenMainWnd(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FullScreenMainWnd),
    m_bMainWinFull(false),
    m_bCentrlWinFull(false)
{
    ui->setupUi(this);
    ui->statusBar->showMessage(tr("statusBar"));

}

FullScreenMainWnd::~FullScreenMainWnd()
{
    delete ui;
}

/**
 * @brief 主窗口全屏
 */
void FullScreenMainWnd::on_pushButton_clicked()
{
    m_bMainWinFull = !m_bMainWinFull;
    if (m_bMainWinFull)
        showFullScreen();
    else
        showNormal();
}

/**
 * @brief 主窗口中的中心 widget全屏
 */
void FullScreenMainWnd::on_pushButton_2_clicked()
{
    Qt::WindowFlags flgs = ui->centralWidget->windowFlags();
    qDebug() << flgs;

    m_bCentrlWinFull = !m_bCentrlWinFull;
    if (m_bCentrlWinFull)
    {
        ui->centralWidget->setWindowFlags( flgs|Qt::Window );
        ui->centralWidget->showFullScreen();
    }
    else
    {
        ui->centralWidget->setWindowFlags( flgs& (~Qt::Window) );
        ui->centralWidget->showNormal();
    }
}

/**
 * @brief 其他 widget 全屏
 */
void FullScreenMainWnd::on_pushButton_3_clicked()
{
    //QWidget *pWidget = ui->statusBar; // 状态栏全屏
    QWidget *pWidget = ui->pushButton_3;   // 本身按钮全屏

    Qt::WindowFlags flgs = pWidget->windowFlags();
    qDebug() << flgs;

    m_bStatusBarFull = !m_bStatusBarFull;
    if (m_bStatusBarFull)
    {

        qDebug() << tr("pWidget->isWindow()= ") << pWidget->isWindow();
        qDebug() << tr("before ") << pWidget->parentWidget();
        pWidget->setWindowFlags( flgs|Qt::Window );
        pWidget->showFullScreen();
        qDebug() << tr("after ") << pWidget->parentWidget();
        qDebug() << tr("pWidget->isWindow()= ") << pWidget->isWindow();
    }
    else
    {
        qDebug() << tr("before ") << pWidget->parentWidget();
        qDebug() << tr("pWidget->isWindow()= ") << pWidget->isWindow();
        pWidget->setWindowFlags( flgs& (~Qt::Window) );
        pWidget->showNormal();

        qDebug() << tr("after ") << pWidget->parentWidget();
        qDebug() << tr("pWidget->isWindow()= ") << pWidget->isWindow();

    }
}
