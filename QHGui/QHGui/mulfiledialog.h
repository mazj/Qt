#ifndef MULFILEDIALOG_H
#define MULFILEDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QMap>

class QTreeWidgetItem;

// �����ⲿʹ��
class _FileDialog : public QFileDialog
{
    Q_OBJECT
public:
    _FileDialog(QWidget *parent, Qt::WindowFlags f)
        : QFileDialog(parent, f)
    {}
    explicit _FileDialog(QWidget *parent = 0,
                         const QString &caption = QString(),
                         const QString &directory = QString(),
                         const QString &filter = QString())
        : QFileDialog(parent, caption, directory, filter)
    {}

public Q_SLOTS:
    virtual void setVisible(bool visible);
};

namespace Ui {
class MulFileDialog;
}

/**
Qt �Դ��ĵõ��ļ��л��ļ��ĶԻ����У��޷�һ�λ�ȡ��� Ŀ¼���޷�һ�λ�ȡ��� ��ͬĿ¼�µ��ļ���
����ļ��Ի������������ʹ��ʾ����  GeneralMainWnd::on_pushButtonShowDlg_clicked()
*/
class MulFileDialog : public QDialog
{
    Q_OBJECT

public:
	//����ظ��ļ���ģʽ
	enum ERepeatFilesMode
	{
		ERepeatFilesNone,	//�����
		ERepeatFilesWarn,	//��ʾ
		ERepeatFilesWarnForbit,  //��ֹ,������ʾ
		ERepeatFilesForbit  //��ֹ��û��ʾ
	};
    explicit MulFileDialog(QWidget *parent = 0, 
		QFileDialog::FileMode fileMode = QFileDialog::ExistingFiles, 
		const QString & caption = QString(),
        const QString & directory = QString(), 
		const QString & filter = QString() );
    ~MulFileDialog();
	//void setFileMode(QFileDialog::FileMode fileMode);
    void setRepeatFilesMode(ERepeatFilesMode repeatFilesMode)
	{ m_eRepeatFilesMode = repeatFilesMode;}
	QStringList getSelectedFiles();

    //static
	/**
	 һ�λ�ȡ������ڵĿ����ڶ����ͬĿ¼�µ��ļ�
	*/
    static QStringList getOpenFileNames ( QWidget * parent = 0,
                                    ERepeatFilesMode repeatFilesMode = ERepeatFilesNone,
                                   const QString & caption = QString(),
                                   const QString & dir = QString(),
                                   const QString & filter = QString() );

public Q_SLOTS:
    void fileDialogAccept();
    virtual void accept();
    virtual void reject();
    //void slotEditFile();
    void slotDellFile();
    void destroyButton(QObject* obj);

private:
    Ui::MulFileDialog *ui;

    _FileDialog *m_pFileDialog;
    QMap<QPushButton*, QTreeWidgetItem*> m_itemMap;
	ERepeatFilesMode m_eRepeatFilesMode;
};

#endif // MULFILEDIALOG_H
