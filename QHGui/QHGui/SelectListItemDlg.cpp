
#include "SelectListItemDlg.h"
#include <QDesktopWidget>
#include <QApplication>
#include <QtGui>


SelectListItemDlg::SelectListItemDlg(QWidget *parent, QStringList devList,
                                     const QString &windowTitle, const QString &selectTitle)
                       : QDialog(parent),
                         m_windowTitle(windowTitle),
                         m_selectTitle(selectTitle)
{
    m_curItemIndex = -1;
    m_disList = devList;
	//�����������öԻ������
    createUi();
}


SelectListItemDlg::~SelectListItemDlg()
{
    m_disList.clear();
}

/**********************************************************************/
/* �������ƣ�createUi                                                  */
/* ���������������������öԻ���ui���棬����ʼ��������ֵ                      */
/**********************************************************************/
void SelectListItemDlg::createUi()
{
	//�����Ի�������沢��������ֵ
//	setWindowIcon(QIcon(":/res/config.png"));
    setWindowTitle(m_windowTitle);
	resize(QSize(450, 280));
     //�Ի����С
	QDesktopWidget *desktop = QApplication::desktop();
	move((desktop->width()-width())/2, (desktop->height()-height())/2);//������ʾ

    m_GroupBox1 = new QGroupBox(m_selectTitle, this);  //����ѡ����
	QVBoxLayout *grid1 = new QVBoxLayout;
    int size = m_disList.size();
   for (int i=0; i < size; i++)
   {
       QString netInfo = m_disList.at(i);
	   m_RadioLst << new QRadioButton(netInfo,this);
       connect(m_RadioLst[i], SIGNAL(clicked (bool)), this, SLOT(slotSelectChanged()));
	   grid1->addWidget(m_RadioLst[i]);
   }
	m_GroupBox1->setLayout(grid1);

	m_pOkButton = new QPushButton(tr("ȷ��"));
	m_pCancelButton = new QPushButton(tr("ȡ��"));
	QHBoxLayout *hLayout = new QHBoxLayout();
    QSpacerItem *horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding,
                                                    QSizePolicy::Minimum);
    hLayout->addItem(horizontalSpacer);
	hLayout->addWidget(m_pOkButton);
	hLayout->addWidget(m_pCancelButton);

	QVBoxLayout *vbox = new QVBoxLayout;
	vbox->addWidget(m_GroupBox1);
	vbox->addLayout(hLayout);
		
	setLayout(vbox);
	
	//������Ϣ���� -- ȡ���ͽ����Լ��ָ�Ĭ��ʱ������ť��Ϣ��Ӧ
	connect(m_pOkButton, SIGNAL(clicked()), this, SLOT(accept()));
	connect(m_pCancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

/**
 * @brief SelectListItemDlg::slotSelectChanged
 */
void SelectListItemDlg::slotSelectChanged()
{
	if (QRadioButton *radioBut = qobject_cast<QRadioButton*>(sender()))
	{
		int index = m_RadioLst.indexOf(radioBut);
        if ((index < m_disList.size()) && (index >= 0))//��źϷ��Լ��
		{
            m_curItemIndex = index;//����ѡ��radioButtom��Ϣ
		}
	}
}

/**
 * �õ���ǰ����Ŀ
 * @return
 */
int  SelectListItemDlg::GetCurIndex()
{
    return m_curItemIndex;
}

/**
 * ���õ�ǰ����Ŀ
 * @param currentIndex
 */
void SelectListItemDlg::SetCurIndex(int currentIndex)
{
	if(currentIndex < 0) 
	{
		return;
    }

    if (currentIndex >= m_disList.size())
	{
		return;
	}
    m_curItemIndex = currentIndex;

    // ���õ�ǰ��Ŀ����
	QRadioButton *radioBut = m_RadioLst.at(currentIndex);
	radioBut->setChecked(true);
}

void SelectListItemDlg::accept()
{  
	QDialog::accept();
}

void SelectListItemDlg::reject()
{  
	QDialog::reject();
}
