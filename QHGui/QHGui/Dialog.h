#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QBoxLayout>
#include <QPointer>

/**
 * @brief �Ի���ģ��
 * ���� ˮƽ��ֱ�� ȷ��ȡ����ť�ĶԻ��� �Ի���ģ��,������ Accept �� Reject ǰ���źţ����û�ȥѡ���ǹ�
 Accept �� Reject
 */
class Dialog : public QDialog
{
    Q_OBJECT
public:
    explicit Dialog(QWidget *parent = 0);
    bool setContent(QWidget *content, int layoutOrientation);

signals:
    /**
     *  ׼���ڷ� reject �ź�ǰ�����źţ�
     * �û������� reject ��true ��false �����û��ֹ �������� reject �źŷ���
     * @param isModal �Ƿ��� model��
     * @param reject
     */
    void willReject(bool isModal, bool &reject);
    /**
     *  ׼���ڷ� accept �ź�ǰ�����źţ�
     * �û������� accept ��true ��false �����û��ֹ �������� accept �źŷ���
     * @param isModal �Ƿ��� model��
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
