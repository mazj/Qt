#include "CornerPromptBox.h"
#include <QCloseEvent>
#include <QDesktopWidget>
#include <QPropertyAnimation>
#include <QRect>
#include <QDialog>
#include <QHBoxLayout>
#include <QLabel>



/**
 * @brief CornerPromptBox::CornerPromptBox
 * @param useAnimation 是否使用动画
 * @param hasBorder  是否有边框
 */
CornerPromptBox::CornerPromptBox(bool useAnimation, bool hasBorder)
    :
      //QMessageBox(Icon(), QString(), QString(), QMessageBox::NoButton),
     m_bUseAnimation(useAnimation),
     m_animation( new QPropertyAnimation(this, "pos") ),
     m_content(NULL),
     m_contentType(ContentNone)
{
#if 1
    Qt::WindowFlags type = windowFlags();
    if (!hasBorder)
        type |= (Qt::FramelessWindowHint);

    type |= Qt::WindowStaysOnTopHint;   // 始终在最前

    this->setWindowFlags(type);
#else // old
    if (!hasBorder)
        this->setWindowFlags(Qt::FramelessWindowHint);
#endif
    m_timer.setSingleShot(true);

    m_layout = new QHBoxLayout();
    m_lable = new QLabel(this);
    m_layout->addWidget(m_lable);
    m_contentType = ContentText;

    setLayout(m_layout);
}

CornerPromptBox::~CornerPromptBox()
{
}

/**
 * 设置使用动画
 * @param use
 */
void CornerPromptBox::setUseAnimation(bool use)
{
    m_bUseAnimation = use;
}

/**
 *
 * @param text
 * \sa setContent(QWidget *w)
 */
/**
 * @brief 设置显示内容
 * @param text 显示内容
 * @param pFont 以何种字体显示
 */
void CornerPromptBox::setContent(const QString &text, const QFont *pFont)
{
    if (pFont)
        m_lable->setFont(*pFont);

    if (m_contentType == ContentWidget)
    {
       m_layout->removeWidget(m_content);
       m_content = NULL;

       m_layout->addWidget(m_lable);

       m_lable->setText(text);
    }
    else if (m_contentType == ContentText)
    {
        m_lable->setText(text);
    }
    else
    {
        Q_ASSERT(0);
    }

    m_contentType = ContentText;
}

/**
 *  设置显示一个  QWidget
 * @param w
 * \sa setContent(const QString &text)
 */
void CornerPromptBox::setContent(QWidget *w)
{
    Q_ASSERT(w);

    if (m_contentType == ContentText)
    {
        m_layout->removeWidget(m_lable);
        m_layout->addWidget(w);
        m_content = w;
    }
    else if (m_contentType == ContentWidget)
    {
        m_layout->removeWidget(m_content);
        m_layout->addWidget(w);
        m_content = w;
    }
    else
    {
        Q_ASSERT(0);
    }

    m_contentType = ContentWidget;
}


/**
 *  显示提示框
 * @param duration 消息框停留时间
 */
void CornerPromptBox::showMsg(int duration)
{
    // 停止可能进行的动画
    disconnect(&m_timer, SIGNAL(timeout()), this, 0);
    m_timer.stop();
    disconnect(m_animation, SIGNAL(finished()), this, 0);
    m_animation->stop();

    //显示弹出框动画
    if (m_bUseAnimation)
    {
        int t = 1000;
        show();  //show 必须在 move前面，不知为啥

        //隐藏菜单栏
        QRect r = frameGeometry();
        move((deskRect().width()-r.width()), deskRect().height());

        // 开启动画
        m_animation->setDuration(t);
        m_animation->setStartValue(QPoint(this->x(),this->y()));
        m_animation->setEndValue(QPoint((deskRect().width()-r.width()),
                                        (deskRect().height()-r.height())));
        m_animation->start();

        // 启动滑出的定时器
        //connect(&m_timer, SIGNAL(timeout()), this, SLOT(closeAnimation()));
        m_timer.start(t+duration);
    }
    else
    {
        show();  //show 必须在 move前面，不知为啥
        QRect r = frameGeometry();
        move((deskRect().width()-r.width()), deskRect().height()-r.height());

        // 启动隐藏的定时器
       // connect(&m_timer, SIGNAL(timeout()), this, SLOT(hide()));
        m_timer.start(duration);
    }

    connect(&m_timer, SIGNAL(timeout()), this, SLOT(slotHideMsg()));
}

void CornerPromptBox::slotHideMsg()
{
    // 断开原来的信号
    disconnect(&m_timer, SIGNAL(timeout()), this, 0);
    m_timer.stop();
    disconnect(m_animation, SIGNAL(finished()), this, 0);
    m_animation->stop();

    if (m_bUseAnimation)
    {
        closeAnimation();
    }
    else
    {
        hide();
    }
}

void CornerPromptBox::closeEvent(QCloseEvent *e)
{
    e->accept();
}

const QRect CornerPromptBox::deskRect()
{
//    return m_desktop.availableGeometry();
    return m_desktop.screenGeometry();
}

//关闭动画
void CornerPromptBox::closeAnimation()
{
    //弹出框回去动画
    QRect r = frameGeometry();
    m_animation->setStartValue(QPoint(this->x(),this->y()));
    m_animation->setEndValue(QPoint(/*(deskRect().width()-r.width())*/ this->x(),
                                    deskRect().height()));
    //m_animation->setEndValue(QPoint((m_desktop.availableGeometry().width()-this->width()),m_desktop.availableGeometry().height()));
    m_animation->start();

    //弹回动画完成后隐藏
    connect(m_animation, SIGNAL(finished()), this, SLOT(_hide()));
    disconnect(&m_timer, SIGNAL(timeout()), this, SLOT(closeAnimation()));
}

void CornerPromptBox::_hide()
{
    disconnect(m_animation, SIGNAL(finished()),this,SLOT(_hide()));
    disconnect(&m_timer, SIGNAL(timeout()),this,SLOT(_hide()));
    hide();
}
