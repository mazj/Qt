#ifndef SYSTEMTRAYICON_H
#define SYSTEMTRAYICON_H

#include <QSystemTrayIcon>

class QMenu;

/**
 * 扩展 QSystemTrayIcon 的功能，扩展的功能有
 *  右键单击 弹出 最大 最小 退出 菜单
 *  双击显示 窗口
 *
 * \bug 有时候双击显示 窗口, 窗口不显示在最上层桌面上，可能会被别的窗口挡住.
 */
class SystemTrayIcon : public QSystemTrayIcon
{
    Q_OBJECT
public:
    explicit SystemTrayIcon(QWidget *pWindow);

signals:
//    void sigWindowShowNormal();
//    void sigWindowHide();

public slots:
private slots:
    void iconActivated(QSystemTrayIcon::ActivationReason reason);

private:
    void creatTrayMenu();
    void creatTrayIcon();

private:
    QWidget *m_pWindow;
    QMenu *m_pMenu;
};

#endif // SYSTEMTRAYICON_H
