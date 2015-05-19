#ifndef STATESETTINGSTACKWGT_H
#define STATESETTINGSTACKWGT_H

#include <QStackedWidget>
#include <QPointer>


/**
 * @brief
 *������ ״̬widget�ϵ�һ��͸��widget����Ҫ��Ϊ�� ��ȡ˫���¼�
 */
class LucidWgt : public QWidget
{
    Q_OBJECT
public:
    LucidWgt(QWidget *p) : QWidget(p) {}
    virtual ~LucidWgt() {}

signals:
    void sigDoubleClick();

protected:
    void mouseDoubleClickEvent(QMouseEvent *);
    bool eventFilter(QObject *, QEvent *);
};

/**
 * @brief ������ʾ״̬������״̬���ܵ�ջwidget,
 * ��ò�Ҫ��ʹ�� QStackedWidget �ĺ���������״̬���ң�ʹ�ø����ṩ�ĺ���
 * ����ʾ״̬������״̬ת�������˫��ʵ��
 *
 */
class StateSettingStackWgt : public QStackedWidget
{
    Q_OBJECT
public:
    explicit StateSettingStackWgt(QStackedWidget *parent = 0);
    void setStateWidget(QWidget *w);
    void setSettingWidget(QWidget *w, int orientation);
    bool showStateWidget(bool accept = true);
    QWidget *removeSettingWidget();
    QWidget *removeStateWidget();

    bool enableStateToSetting(bool en);
    bool enableSettingToState(bool en);

signals:

    /**
     *  ��״̬widget ������widget �л�ǰ�����źţ�
     * ���źŷ��غ���ٴμ��ʹ��״̬�����Կ�����ֱ���������͵Ĳ��иı�ʹ��
     * @param en Ŀǰ��תʹ��״̬
     */
    void sigStateToSetting(bool en);

    /**
     *  ������widget ��״̬widget �л�ǰ�����źţ�
     *���źŷ��غ���ٴμ��ʹ��״̬�����Կ�����ֱ���������͵Ĳ��иı�ʹ��
     * @param accept �Ի������Ƿ�Ϊ accepted
     * @param en Ŀǰ��תʹ��״̬
     */
    void sigSettingToState(bool accept, bool en);

public slots:
private slots:
    void slotShowSetting();
    void slotShowState(int n);

private:
    bool _showStateWidget(bool accept);

private:
    QPointer<QWidget> m_pStateWgt;
    QPointer<QWidget> m_pSettingWgt;
    QPointer<LucidWgt> m_pLucidWgt;

    bool m_bToSetting;
    bool m_bToState;
};

#endif // STATESETTINGSTACKWGT_H
