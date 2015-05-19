#ifndef SYSTEMTRAYICON_H
#define SYSTEMTRAYICON_H

#include <QSystemTrayIcon>

class QMenu;

/**
 * ��չ QSystemTrayIcon �Ĺ��ܣ���չ�Ĺ�����
 *  �Ҽ����� ���� ��� ��С �˳� �˵�
 *  ˫����ʾ ����
 *
 * \bug ��ʱ��˫����ʾ ����, ���ڲ���ʾ�����ϲ������ϣ����ܻᱻ��Ĵ��ڵ�ס.
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
