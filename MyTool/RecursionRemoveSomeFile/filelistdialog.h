#ifndef FILELISTDIALOG_H
#define FILELISTDIALOG_H

#include <QDialog>

namespace Ui {
class FileListDialog;
}

class QTreeWidgetItem;
class FileListDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FileListDialog(QWidget *parent = 0);
    ~FileListDialog();
    void setFileList(const QMultiMap<QString, QString>& filePathMap);

signals:
    void sigRefresh();
private slots:
    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_refreshButton_clicked();

private:
    Ui::FileListDialog *ui;
};

#endif // FILELISTDIALOG_H
