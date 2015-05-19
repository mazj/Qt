#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QBoxLayout>
#include <QPointer>

/**
 * @brief 对话框模板
 * 带有 水平或垂直的 确定取消按钮的对话框 对话框模板,且能在 Accept 和 Reject 前发信号，让用户去选择是够
 Accept 或 Reject
 */
class Dialog : public QDialog
{
    Q_OBJECT
public:
    explicit Dialog(QWidget *parent = 0);
    bool setContent(QWidget *content, int layoutOrientation);

signals:
    /**
     *  准备在发 reject 信号前发改信号，
     * 用户可设置 reject 成true 或false 来启用或禁止 接下来的 reject 信号发送
     * @param isModal 是否是 model的
     * @param reject
     */
    void willReject(bool isModal, bool &reject);
    /**
     *  准备在发 accept 信号前发改信号，
     * 用户可设置 accept 成true 或false 来启用或禁止 接下来的 accept 信号发送
     * @param isModal 是否是 model的
     * @param accept
     */
    void willAccept(bool isModal, bool &accept);

public slots:
    void reject();
    void accept();

private:
    QWidget *m_pCentreWidget;
    bool m_reject;
    bool m_accept;
};

#endif // DIALOG_H
