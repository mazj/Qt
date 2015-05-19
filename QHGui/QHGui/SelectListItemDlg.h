
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
 * 选择 互斥的 list条目的 对话框，每一条是一行文字
 * Exclusive
 */
class SelectListItemDlg : public QDialog
{
	Q_OBJECT
public:
    SelectListItemDlg(QWidget *parent, QStringList  disList,
                      const QString& windowTitle = "参数设置",
                      const QString& selectTitle = "请选择");
	
    virtual ~SelectListItemDlg();
    int  GetCurIndex();
    void SetCurIndex(int currentIndex);
private:
    void              createUi(); //创建参数设置对话框ui界面，并初始化其属性值
public slots:	//槽函数定义
    void              slotSelectChanged();

	virtual void      accept();//将参数设置对话框中的设置值进行保存

	virtual void      reject();//将参数设置对话框中的设置值进行恢复
	
protected:
    //bool m_bValid;
    QStringList          m_disList; ///! 显示列表

	QList<QRadioButton*> m_RadioLst;   //记录4个RadioButtom对象指针

    QGroupBox            *m_GroupBox1;
	
	QPushButton          *m_pOkButton;    //确定按钮
	QPushButton          *m_pCancelButton;//取消按钮
    int                  m_curItemIndex;    //当前 item
    QString     m_windowTitle;  ///！ 窗口标题
    QString     m_selectTitle;  ///!  选择标题
};

#endif // PARASETDLG_H
