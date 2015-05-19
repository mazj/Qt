#include "mulfiledialog.h"
#include "ui_mulfiledialog.h"

#include <QPushButton>
#include <QMessageBox>

//只显示不隐藏，因为默认的 非模态的 QFileDialog 会隐藏
void _FileDialog::setVisible(bool visible)
{
    if (visible)
        return QFileDialog::setVisible(visible);
    else
        ; //empty
}

MulFileDialog::MulFileDialog(QWidget *parent, QFileDialog::FileMode fileMode,
                             const QString & caption,
                             const QString & directory, const QString & filter) :
    QDialog(parent),
    ui(new Ui::MulFileDialog),
	m_eRepeatFilesMode(ERepeatFilesNone)
{
    ui->setupUi(this);

    setWindowTitle(caption);

    ui->treeWidget->clear();
    ui->treeWidget->setColumnWidth(0, 50);
    ui->treeWidget->setColumnHidden(0, true);
    ui->treeWidget->setColumnWidth(1, 50);

    m_pFileDialog = new _FileDialog(0, caption, directory, filter);
    m_pFileDialog->setFileMode(fileMode);
    //m_pFileDialog->setFileMode(QFileDialog::ExistingFiles);

    ui->verticalLayout_3->insertWidget(0, m_pFileDialog);

    QObject::connect(m_pFileDialog, SIGNAL(accepted()), this, SLOT(fileDialogAccept()));
    //QObject::connect(pFileDialog, SIGNAL(rejected()), MulFileDialog, SLOT(reject()));

    m_pFileDialog->show();
}

MulFileDialog::~MulFileDialog()
{
    delete ui;
}

QStringList MulFileDialog::getSelectedFiles()
{
    QStringList files;
    int count = ui->treeWidget->topLevelItemCount();

    for(int i=0;i<count; ++i)
    {
        QTreeWidgetItem* pItem = ui->treeWidget->topLevelItem(i);
        files << pItem->text(2);
    }

    return files;
}

void MulFileDialog::fileDialogAccept()
{
    QStringList files = m_pFileDialog->selectedFiles();
	QStringList allFiles;
	if (m_eRepeatFilesMode != ERepeatFilesNone)
	{
		allFiles = getSelectedFiles();
	}

    foreach (const QString& file, files) {

		if (m_eRepeatFilesMode == ERepeatFilesWarn)
		{
			if ( allFiles.contains(file) )
			{
				QMessageBox::StandardButton btn = QMessageBox::question(this, tr("提示"), 
					tr("已经包含所选文件，还要添加文件 %1 吗？").arg(file), 
					QMessageBox::StandardButton::Yes
					|QMessageBox::StandardButton::No
                    |QMessageBox::StandardButton::YesToAll
					|QMessageBox::StandardButton::NoToAll, 
					QMessageBox::StandardButton::No);
				if ( btn == QMessageBox::StandardButton::Yes )
				{
					//empty
				}
				if ( btn == QMessageBox::StandardButton::YesToAll )
				{
					m_eRepeatFilesMode = ERepeatFilesNone;
				}
				else if (btn == QMessageBox::StandardButton::No)
				{
					continue;
				}
				else if (btn == QMessageBox::StandardButton::NoToAll)
				{
                    m_eRepeatFilesMode = ERepeatFilesWarnForbit;
					continue;
				}
				else
				{
					// empty
				}
			}
		}
		else if(ERepeatFilesWarnForbit == m_eRepeatFilesMode)
		{
			if ( allFiles.contains(file) )
			{
				QMessageBox::warning(this, tr("提示"), tr("已经包含了文件 %1 .").arg(file));
				continue;
			}
		}
		else if(ERepeatFilesForbit == m_eRepeatFilesMode)
		{
			if ( allFiles.contains(file) )
			{
				continue;
			}
		}
		else 
		{
			//empty
		}

        QStringList clos;
        clos << QString() << QString() << file;
        QTreeWidgetItem *pItem = new QTreeWidgetItem(clos);
        ui->treeWidget->addTopLevelItem(pItem );

        QPushButton *pButton;
//        pButton = new QPushButton(tr("编辑"));
//        m_itemMap.insert(pButton, pItem);
//        connect(pButton, SIGNAL(destroyed(QObject*)),
//                this, SLOT(destroyButton(QObject*)));
//        connect(pButton, SIGNAL(clicked()), this, SLOT(slotEditFile()));
//        ui->treeWidget->setItemWidget(pItem, 0, pButton);

        pButton = new QPushButton(tr("删除"));
        m_itemMap.insert(pButton, pItem);
        connect(pButton, SIGNAL(destroyed(QObject*)),
                this, SLOT(destroyButton(QObject*)));
        connect(pButton, SIGNAL(clicked()), this, SLOT(slotDellFile()));
        ui->treeWidget->setItemWidget(pItem, 1, pButton);
    }

	
}

void MulFileDialog::accept()
{
    QDialog::accept();
}

void MulFileDialog::reject()
{
    QDialog::reject();
}

//void MulFileDialog::slotEditFile()
//{
//    QPushButton* pButton = qobject_cast<QPushButton*>(sender());
//    if (pButton)
//    {
//        delete m_itemMap.value(pButton);
//    }
//}

void MulFileDialog::slotDellFile()
{
    QPushButton* pButton = qobject_cast<QPushButton*>(sender());
    if (pButton)
    {
        delete m_itemMap.value(pButton);
    }
//    QTreeWidgetItem *pItem = ui->treeWidget->currentItem();
//    delete pItem;
}

void MulFileDialog::destroyButton(QObject* obj)
{
    QPushButton* pButton = (QPushButton*)(obj);
    if (pButton)
    {
        m_itemMap.remove(pButton);
    }
}

QStringList MulFileDialog::getOpenFileNames ( QWidget * parent,
								   ERepeatFilesMode repeatFilesMode,
                                   const QString & caption ,
                                   const QString & dir,
                                   const QString & filter )
{
    MulFileDialog mfd(parent, QFileDialog::ExistingFiles, caption, dir, filter);
	mfd.setRepeatFilesMode(repeatFilesMode);
    mfd.exec();
    return mfd.getSelectedFiles();
}
