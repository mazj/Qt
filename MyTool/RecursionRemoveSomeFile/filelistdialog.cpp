#include "filelistdialog.h"
#include "ui_filelistdialog.h"

#include <QDir>
#include <QProcess>

FileListDialog::FileListDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileListDialog)
{
    ui->setupUi(this);

}

FileListDialog::~FileListDialog()
{
    delete ui;
}

void FileListDialog::setFileList(const QMultiMap<QString, QString>& filePathMap)
{
     ui->treeWidget->clear();

    QMultiMap<QString, QString>::const_iterator it
            = filePathMap.begin();
    for(; it != filePathMap.end(); ++it)
    {
        QStringList list;
        list << it.key() << it.value();
        ui->treeWidget->addTopLevelItem(new QTreeWidgetItem(list));
    }

}

void FileListDialog::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    //1.QProcess::startDetached("explorer "+ Path )

    //2.QDesktopServices::openUrl(QUrl::fromLocalFile(path));

    QString path = item->text(1);
    path = QDir::toNativeSeparators(path);
    QProcess::startDetached("explorer "+ tr("/select, ")
                            + tr("\"") + path + tr("\""));

}

void FileListDialog::on_refreshButton_clicked()
{
    emit sigRefresh();
}
