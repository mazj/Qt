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
 * @param useAnimation �Ƿ�ʹ�ö���
 * @param hasBorder  �Ƿ��б߿�
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

    type |= Qt::WindowStaysOnTopHint;   // ʼ������ǰ

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
 * ����ʹ�ö���
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
 * @brief ������ʾ����
 * @param text ��ʾ����
 * @param pFont �Ժ���������ʾ
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
 *  ������ʾһ��  QWidget
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
 *  ��ʾ��ʾ��
 * @param duration ��Ϣ��ͣ��ʱ��
 */
void CornerPromptBox::showMsg(int duration)
{
    // ֹͣ���ܽ��еĶ���
    disconnect(&m_timer, SIGNAL(timeout()), this, 0);
    m_timer.stop();
    disconnect(m_animation, SIGNAL(finished()), this, 0);
    m_animation->stop();

    //��ʾ�����򶯻�
    if (m_bUseAnimation)
    {
        int t = 1000;
        show();  //show ������ moveǰ�棬��֪Ϊɶ

        //���ز˵���
        QRect r = frameGeometry();
        move((deskRect().width()-r.width()), deskRect().height());

        // ��������
        m_animation->setDuration(t);
        m_animation->setStartValue(QPoint(this->x(),this->y()));
        m_animation->setEndValue(QPoint((deskRect().width()-r.width()),
                                        (deskRect().height()-r.height())));
        m_animation->start();

        // ���������Ķ�ʱ��
        //connect(&m_timer, SIGNAL(timeout()), this, SLOT(closeAnimation()));
        m_timer.start(t+duration);
    }
    else
    {
        show();  //show ������ moveǰ�棬��֪Ϊɶ
        QRect r = frameGeometry();
        move((deskRect().width()-r.width()), deskRect().height()-r.height());

        // �������صĶ�ʱ��
       // connect(&m_timer, SIGNAL(timeout()), this, SLOT(hide()));
        m_timer.start(duration);
    }

    connect(&m_timer, SIGNAL(timeout()), this, SLOT(slotHideMsg()));
}

void CornerPromptBox::slotHideMsg()
{
    // �Ͽ�ԭ�����ź�
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

//�رն���
void CornerPromptBox::closeAnimation()
{
    //�������ȥ����
    QRect r = frameGeometry();
    m_animation->setStartValue(QPoint(this->x(),this->y()));
    m_animation->setEndValue(QPoint(/*(deskRect().width()-r.width())*/ this->x(),
                                    deskRect().height()));
    //m_animation->setEndValue(QPoint((m_desktop.availableGeometry().width()-this->width()),m_desktop.availableGeometry().height()));
    m_animation->start();

    //���ض�����ɺ�����
    connect(m_animation, SIGNAL(finished()), this, SLOT(_hide()));
    disconnect(&m_timer, SIGNAL(timeout()), this, SLOT(closeAnimation()));
}

void CornerPromptBox::_hide()
{
    disconnect(m_animation, SIGNAL(finished()),this,SLOT(_hide()));
    disconnect(&m_timer, SIGNAL(timeout()),this,SLOT(_hide()));
    hide();
}
