
#ifndef SelectListItemDlg_H
#define SelectListItemDlg_H


#include <QDialog>
#include <QComboBox>
#include <QLabel>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QRadioButton>


/**
 * ѡ�� ����� list��Ŀ�� �Ի���ÿһ����һ������
 * Exclusive
 */
class SelectListItemDlg : public QDialog
{
	Q_OBJECT
public:
    SelectListItemDlg(QWidget *parent, QStringList  disList,
                      const QString& windowTitle = "��������",
                      const QString& selectTitle = "��ѡ��");
	
    virtual ~SelectListItemDlg();
    int  GetCurIndex();
    void SetCurIndex(int currentIndex);
private:
    void              createUi(); //�����������öԻ���ui���棬����ʼ��������ֵ
public slots:	//�ۺ�������
    void              slotSelectChanged();

	virtual void      accept();//���������öԻ����е�����ֵ���б���

	virtual void      reject();//���������öԻ����е�����ֵ���лָ�
	
protected:
    //bool m_bValid;
    QStringList          m_disList; ///! ��ʾ�б�

	QList<QRadioButton*> m_RadioLst;   //��¼4��RadioButtom����ָ��

    QGroupBox            *m_GroupBox1;
	
	QPushButton          *m_pOkButton;    //ȷ����ť
	QPushButton          *m_pCancelButton;//ȡ����ť
    int                  m_curItemIndex;    //��ǰ item
    QString     m_windowTitle;  ///�� ���ڱ���
    QString     m_selectTitle;  ///!  ѡ�����
};

#endif // PARASETDLG_H
