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
  Ϊ��ʱ�̱��ָ���widgetһ����
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
 * @brief ����״̬widget
 * w �ᱻ��һ����͸��widget��w������Ȩ�� StateSettingStackWgt
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

    //Ϊ�˻�ȡ״̬widget�Ĵ�С���� m_pLucidWgt ��״̬widget����һ����
    m_pStateWgt->installEventFilter(m_pLucidWgt);

    //����˫���Ĳ�
    connect(m_pLucidWgt, SIGNAL(sigDoubleClick()),
            SLOT(slotShowSetting()));

    // ʹ�� QStackedWidget �ķ����ӵ� ջ��
    addWidget(m_pStateWgt);
    setCurrentWidget(m_pStateWgt);
}

/**
  ���� ����widget
 * �� orientationΪ ˮƽ�ʹ�ֱ֮һʱ��ʹ�� ˮƽ��ֱ�����öԻ���ģ�ͣ�
 * ����ʹ�����öԻ���ģ�ͣ����û� ����showStateWidget() ��������widget��״̬widget����ת��
 * @param w
 * @param orientation ���ַ���ȡQt::Horizontal	0x1 �� Qt::Vertical	0x2 �� 0

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
        Q_ASSERT_X(0, "", "���� orientation ����");
    }

    // ʹ�� QStackedWidget �ķ����ӵ� ջ��
    addWidget(m_pSettingWgt);

}

/**
 * ��ʾ״̬widget��һ�� �� ����widget��ʹ�����öԻ���ģ�� ʱ���ⲿ���øú�������
 * ����widget ��ת�� ״̬widget����ʹ���ڲ��Ի���ģʽʱ�������øú���
 * \sa setSettingWidget()
 * @return �ɹ�������
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
   ��״̬ widget�� ����widget��ת��ʹ�ܿ���
 * @param en
 * @return
 */
bool StateSettingStackWgt::enableStateToSetting(bool en)
{
    m_bToSetting = en;
    return en;
}

/**
   ������widget �� ״̬ widget ��ת��ʹ�ܿ���
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
 * @param accept ���öԻ���Ľ���Ƿ��� acceptd
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
