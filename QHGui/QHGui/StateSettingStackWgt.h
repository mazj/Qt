#ifndef STATESETTINGSTACKWGT_H
#define STATESETTINGSTACKWGT_H

#include <QStackedWidget>
#include <QPointer>


/**
 * @brief
 *覆盖在 状态widget上的一个透明widget，主要是为了 获取双击事件
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
 * @brief 具有显示状态和设置状态功能的栈widget,
 * 最好不要再使用 QStackedWidget 的函数，以免状态混乱，使用该类提供的函数
 * 从显示状态到设置状态转换用鼠标双击实现
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
     *  在状态widget 到设置widget 切换前发该信号，
     * 该信号返回后会再次检测使能状态，所以可以在直接连接类型的槽中改变使能
     * @param en 目前跳转使能状态
     */
    void sigStateToSetting(bool en);

    /**
     *  在设置widget 到状态widget 切换前发该信号，
     *该信号返回后会再次检测使能状态，所以可以在直接连接类型的槽中改变使能
     * @param accept 对话框结果是否为 accepted
     * @param en 目前跳转使能状态
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
