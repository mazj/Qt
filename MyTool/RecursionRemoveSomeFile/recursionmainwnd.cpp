#include "recursionmainwnd.h"
#include "ui_recursionmainwnd.h"

#include <QDebug>
#include <QDir>
#include <QMessageBox>
#include "QFileDialog"
#include "filelistdialog.h"

RecursionMainWnd::RecursionMainWnd(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RecursionMainWnd),
    m_pFileListDlg(new FileListDialog)
{
    ui->setupUi(this);
    connect(m_pFileListDlg, SIGNAL(sigRefresh()), this, SLOT(slotRefresh()));
}

RecursionMainWnd::~RecursionMainWnd()
{
    delete ui;
}

void RecursionMainWnd::slotRefresh()
{
    m_pFileListDlg->setFileList(m_filePathMap);
    m_pFileListDlg->show();
    m_pFileListDlg->activateWindow();
}

void RecursionMainWnd::on_pushButtonDir_clicked()
{
    QString sDir = QFileDialog::getExistingDirectory(this, tr(" 选择递归删除的目录"));
    if (!sDir.isEmpty())
        ui->dirsListWidget->addItem(sDir);
}

// 递归列出文件
void RecursionMainWnd::listFile(const QString& sDir,
                                const QStringList& skipedFolders,
                                const QStringList& skipedFiles,
                                const QStringList& skipedPath)
{
    QDir dir(sDir);
    dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot
                  | QDir::NoSymLinks | QDir::Hidden);
    QFileInfoList list = dir.entryInfoList();

     for (int i = 0; i < list.size(); ++i) {
         QFileInfo fileInfo = list.at(i);
         if (fileInfo.isDir())
         {
             qDebug() << tr("folder:") << fileInfo.fileName();
             if (skipedFolders.contains(fileInfo.fileName()))
                 continue;

             if (skipedPath.contains(fileInfo.absoluteFilePath()))
                 continue;

             qDebug() << tr("entry folder:") << fileInfo.absoluteFilePath();
             listFile(fileInfo.absoluteFilePath(), skipedFolders,
                      skipedFiles, skipedPath);
         }
         else
         {
             qDebug() << tr("file:") << fileInfo.fileName();
            if (skipedFiles.contains(fileInfo.fileName()))
                continue;
            if (skipedPath.contains(fileInfo.absoluteFilePath()))
                continue;

            qDebug() << tr("inset file:") << fileInfo.absoluteFilePath();
            m_filePathMap.insertMulti(fileInfo.fileName(), fileInfo.absoluteFilePath());
         }
     }
}


void RecursionMainWnd::on_pushButtonStart_clicked()
{
    QStringList lastDirs;
    QStringList tmpDirs;
    if (!ui->useLastCheckBox->isChecked())
    {
        m_filePathMap.clear();
    }
    else
    {
        lastDirs = m_dirs;
    }

    bool bSkipFolder = ui->checkBoxfolder->isChecked();
    bool bSkipFile = ui->checkBoxFile->isChecked();

    for (int row=0; row<ui->dirsListWidget->count(); ++row) {
        QListWidgetItem *item = ui->dirsListWidget->item(row);
        QStringList folders;
        QStringList files;
        QStringList skipedPath;

        if (bSkipFolder)
            folders = ui->plainTextEditFolder->toPlainText()
                    .split("\n", QString::SkipEmptyParts);
        if (bSkipFile)
            files = ui->plainTextEditFile->toPlainText()
                    .split("\n", QString::SkipEmptyParts);

        //判断上次是否包含
        bool bContinue = false;
        foreach (const QString& sdir, lastDirs) {
            if (item->text() == sdir)
            {
                bContinue = true;
                break;
            }
            else if (sdir.indexOf(item->text()) == 0)
            {
                bContinue = false;
                skipedPath << sdir;
            }
            else if ( item->text().indexOf(sdir) == 0)
            {
                bContinue = true;
                break;
            }
        }

        if (bContinue)
            continue;

        tmpDirs << item->text();
        listFile(item->text(), folders, files, skipedPath);

    }

    if (!tmpDirs.isEmpty())
        m_dirs = tmpDirs;

}

void RecursionMainWnd::on_dirsListWidget_itemDoubleClicked(QListWidgetItem *item)
{
    QMessageBox msgBox;
    msgBox.setText(tr("修改目录？ 删除目录？"));
    QPushButton *modifyButton = msgBox.addButton(tr("修改"), QMessageBox::ApplyRole);
    QPushButton *cancelButton = msgBox.addButton(tr("删除"), QMessageBox::ApplyRole);
    msgBox.addButton(QMessageBox::Cancel);

    msgBox.exec();

    if (msgBox.clickedButton() == modifyButton) {
        QString sDir = QFileDialog::getExistingDirectory(this, tr(" 选择递归删除的目录"),
                                                         item->text());
        if (!sDir.isEmpty())
            item->setText(sDir);
    } else if (msgBox.clickedButton() == cancelButton) {
         delete item;
    }
}

void RecursionMainWnd::on_showResultButton_clicked()
{
    slotRefresh();
}

void RecursionMainWnd::on_sortButton_clicked()
{
    QStringList dirs;
    for (int row=0; row<ui->dirsListWidget->count(); ++row) {
        QListWidgetItem *item = ui->dirsListWidget->item(row);
        dirs << item->text();
    }

    ui->dirsListWidget->clear();
    dirs.sort();
    ui->dirsListWidget->addItems(dirs);
}
