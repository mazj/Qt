#ifndef MULFILEDIALOG_H
#define MULFILEDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QMap>

class QTreeWidgetItem;

// 不给外部使用
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
Qt 自带的得到文件夹或文件的对话框中，无法一次获取多个 目录，无法一次获取多个 不同目录下的文件。
这个文件对话框可以做到。使用示例见  GeneralMainWnd::on_pushButtonShowDlg_clicked()
*/
class MulFileDialog : public QDialog
{
    Q_OBJECT

public:
	//检查重复文件的模式
	enum ERepeatFilesMode
	{
		ERepeatFilesNone,	//不检查
		ERepeatFilesWarn,	//提示
		ERepeatFilesWarnForbit,  //禁止,但有提示
		ERepeatFilesForbit  //禁止，没提示
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
	 一次获取多个存在的可以在多个不同目录下的文件
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
