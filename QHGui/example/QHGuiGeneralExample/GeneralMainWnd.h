#ifndef GENERALMAINWND_H
#define GENERALMAINWND_H

#include <QMainWindow>

namespace Ui {
class GeneralMainWnd;
}

class CornerPromptBox;
class Dialog;
class GeneralMainWnd : public QMainWindow
{
    Q_OBJECT

public:
    explicit GeneralMainWnd(QWidget *parent = 0);
    ~GeneralMainWnd();

private slots:
    void on_pushButtonCornerPromptBox_clicked();

    void on_pushButtonShowDialog_clicked();

    void slotWillReject(bool isModal, bool &reject);
    void slotWillAccept(bool isModal, bool &accept);
    void slotDialogFinish(int);



    void on_pushButtonGetComboBoxAllItemtext_clicked();

    void on_pushButtonSetComboBoxValue_clicked();

    void on_pushButtonDumpEventFilters_clicked();

    void on_pushButtonDumpObjectTree_clicked();

    void on_pushButtonInitNote_clicked();

    void on_pushButtonInitNoteRename_clicked();

    void on_pushButtonShowDlg_clicked();

private:
    Ui::GeneralMainWnd *ui;

    CornerPromptBox *m_cornerPromptBox;
    Dialog *m_pDialog;
};

#endif // GENERALMAINWND_H
