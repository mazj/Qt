#ifndef RECURSIONMAINWND_H
#define RECURSIONMAINWND_H

#include <QMultiMap>
#include <QMainWindow>

namespace Ui {
class RecursionMainWnd;
}
class QListWidgetItem;
class FileListDialog;
/*
    递归的删除文件
 */
class RecursionMainWnd : public QMainWindow
{
    Q_OBJECT

public:
    explicit RecursionMainWnd(QWidget *parent = 0);
    ~RecursionMainWnd();

private:
    void listFile(const QString& sDir, const QStringList& skipedFolders,
                  const QStringList& skipedFiles, const QStringList &skipedPath);

private slots:
    void slotRefresh();
    void on_pushButtonDir_clicked();

    void on_pushButtonStart_clicked();

    void on_dirsListWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_showResultButton_clicked();

    void on_sortButton_clicked();

private:
    Ui::RecursionMainWnd *ui;
    QMultiMap<QString, QString> m_filePathMap;
    FileListDialog *m_pFileListDlg;
    QStringList m_dirs;
};

#endif // RECURSIONMAINWND_H
