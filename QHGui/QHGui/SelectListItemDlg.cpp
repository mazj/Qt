
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
	//创建参数设置对话框界面
    createUi();
}


SelectListItemDlg::~SelectListItemDlg()
{
    m_disList.clear();
}

/**********************************************************************/
/* 函数名称：createUi                                                  */
/* 功能描述：创建参数设置对话框ui界面，并初始化其属性值                      */
/**********************************************************************/
void SelectListItemDlg::createUi()
{
	//创建对话框窗体界面并设置属性值
//	setWindowIcon(QIcon(":/res/config.png"));
    setWindowTitle(m_windowTitle);
	resize(QSize(450, 280));
     //对话框大小
	QDesktopWidget *desktop = QApplication::desktop();
	move((desktop->width()-width())/2, (desktop->height()-height())/2);//居中显示

    m_GroupBox1 = new QGroupBox(m_selectTitle, this);  //网卡选择栏
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

	m_pOkButton = new QPushButton(tr("确定"));
	m_pCancelButton = new QPushButton(tr("取消"));
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
	
	//建立消息连接 -- 取消和接收以及恢复默认时间间隔按钮消息响应
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
        if ((index < m_disList.size()) && (index >= 0))//编号合法性检查
		{
            m_curItemIndex = index;//设置选中radioButtom信息
		}
	}
}

/**
 * 得到当前的条目
 * @return
 */
int  SelectListItemDlg::GetCurIndex()
{
    return m_curItemIndex;
}

/**
 * 设置当前的条目
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

    // 设置当前条目索引
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
