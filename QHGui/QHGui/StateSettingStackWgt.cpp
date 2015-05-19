#include "StateSettingStackWgt.h"
#include <QEvent>
#include <QResizeEvent>
#include "Dialog.h"

void LucidWgt::mouseDoubleClickEvent(QMouseEvent *e)
{
    (void)e;
    emit sigDoubleClick();
}

/**
  为了时刻保持跟父widget一样大
 *
 * @param o
 * @param e
 * @return
 */
bool LucidWgt::eventFilter(QObject *o, QEvent *e)
{
    if (o == parent() && e->type() == QEvent::Resize)
    {
        QResizeEvent *event = static_cast<QResizeEvent*>(e);
        resize(event->size());
        raise();
    }

    return QWidget::eventFilter(o, e);
}

//////////////////////////////////////////////////////////////////////////
/// \brief StateSettingStackWgt::StateSettingStackWgt
/// \param parent
/////////////////////////////////////////////////////////////////////////

StateSettingStackWgt::StateSettingStackWgt(QStackedWidget *parent) :
    QStackedWidget(parent),
    m_bToSetting(true),
    m_bToState(true)
{
    //setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
}

/**
 * @brief 设置状态widget
 * w 会被加一个子透明widget，w的所有权归 StateSettingStackWgt
 * @param w
 */
void StateSettingStackWgt::setStateWidget(QWidget *w)
{
    Q_ASSERT(w);

    if (m_pStateWgt)
    {
        if (w == m_pSettingWgt)
            return;
        else
            m_pStateWgt->deleteLater();
    }

    m_pStateWgt = w;
    m_pLucidWgt = new LucidWgt(w);
    m_pLucidWgt->resize(w->size());
    m_pLucidWgt->show();
    m_pLucidWgt->raise();

    //为了获取状态widget的大小，将 m_pLucidWgt 和状态widget设置一样大
    m_pStateWgt->installEventFilter(m_pLucidWgt);

    //链接双击的槽
    connect(m_pLucidWgt, SIGNAL(sigDoubleClick()),
            SLOT(slotShowSetting()));

    // 使用 QStackedWidget 的方法加到 栈中
    addWidget(m_pStateWgt);
    setCurrentWidget(m_pStateWgt);
}

/**
  设置 设置widget
 * 当 orientation为 水平和垂直之一时，使用 水平或垂直的内置对话框模型；
 * 否则不使用内置对话框模型，由用户 调用showStateWidget() 激活设置widget到状态widget的跳转。
 * @param w
 * @param orientation 布局方向，取Qt::Horizontal	0x1 或 Qt::Vertical	0x2 或 0

 */
void StateSettingStackWgt::setSettingWidget(QWidget *w, int orientation)
{
    Q_ASSERT(w);
    if (m_pSettingWgt)
    {
        if (w == m_pSettingWgt)
            return;
        else
            m_pSettingWgt->deleteLater();
    }

    if (orientation == Qt::Horizontal)
    {
        Dialog *dialog = new Dialog();
        dialog->setContent(w, Qt::Horizontal);
        connect(dialog, SIGNAL(finished(int)),
                this, SLOT(slotShowState(int)));

        m_pSettingWgt = dialog;
    }
    else if (orientation == Qt::Vertical)
    {
        Dialog *dialog = new Dialog();
        dialog->setContent(w, Qt::Vertical);
        connect(dialog, SIGNAL(finished(int)),
                this, SLOT(slotShowState(int)));

        m_pSettingWgt = dialog;
    }
    else if (orientation == 0)
    {
        m_pSettingWgt = w;
    }
    else
    {
        Q_ASSERT_X(0, "", "参数 orientation 错误");
    }

    // 使用 QStackedWidget 的方法加到 栈中
    addWidget(m_pSettingWgt);

}

/**
 * 显示状态widget，一般 在 设置widget不使用内置对话框模型 时，外部调用该函数来从
 * 设置widget 跳转到 状态widget。在使用内部对话框模式时，不适用该函数
 * \sa setSettingWidget()
 * @return 成功返回真
 */
bool StateSettingStackWgt::showStateWidget(bool accept)
{
    return _showStateWidget(accept);
}

QWidget *StateSettingStackWgt::removeSettingWidget()
{
    if (m_pSettingWgt)
    {
        QWidget *w = m_pSettingWgt;
        removeWidget(m_pSettingWgt);
        m_pSettingWgt = NULL;
        return w;
    }
    else
    {
        return NULL;
    }
}

QWidget *StateSettingStackWgt::removeStateWidget()
{
    if (m_pStateWgt)
    {
        QWidget *w = m_pStateWgt;
        removeWidget(m_pStateWgt);
        m_pStateWgt = NULL;
        return w;
    }
    else
    {
        return NULL;
    }
}

/**
   从状态 widget到 设置widget跳转的使能控制
 * @param en
 * @return
 */
bool StateSettingStackWgt::enableStateToSetting(bool en)
{
    m_bToSetting = en;
    return en;
}

/**
   从设置widget 到 状态 widget 跳转的使能控制
 * @param en
 * @return
 */
bool StateSettingStackWgt::enableSettingToState(bool en)
{
    m_bToState = en;
    return en;
}

void StateSettingStackWgt::slotShowSetting()
{
    if (m_pSettingWgt)
    {
        emit sigStateToSetting(m_bToSetting);
        if (m_bToSetting)
            setCurrentWidget(m_pSettingWgt);
    }
}

void StateSettingStackWgt::slotShowState(int n)
{
    _showStateWidget(n==QDialog::Accepted);
}

/**
 * @brief StateSettingStackWgt::showStateWidget
 * @param accept 设置对话框的结果是否是 acceptd
 * @return
 */
bool StateSettingStackWgt::_showStateWidget(bool accept)
{
    if (m_pStateWgt)
    {
        emit sigSettingToState(accept, m_bToState);
        if (m_bToState)
        {
            setCurrentWidget(m_pStateWgt);
            return true;
        }
    }

    return false;
}
