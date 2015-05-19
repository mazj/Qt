#include "GeneralMainWnd.h"
#include "ui_GeneralMainWnd.h"

#include <cassert>
#include <QMessageBox>
#include <QDebug>
#include <QSettings>
#include <QFileDialog>
#include <QTextCodec>

#include "QHTool/qHelpFunction.h"
#include "QHTool/IniNote.h"

#include <QHGui/qhGui.h>
#include <QHGui/CornerPromptBox.h>
#include <QHGui/Dialog.h>
#include "QHGui/SystemTrayIcon.h"
#include "QHGui/mulfiledialog.h"

GeneralMainWnd::GeneralMainWnd(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GeneralMainWnd),
    m_cornerPromptBox(0),
    m_pDialog(new Dialog(this))
{
    ui->setupUi(this);

    QIcon ic("://picture/iconpng.png");
    setWindowIcon(ic);

    SystemTrayIcon *pSystemTrayIcon = new SystemTrayIcon(this);
    pSystemTrayIcon->setIcon(ic);
    pSystemTrayIcon->setToolTip(tr("ʾ�� һ��� QHTool ��ʹ��"));    //����ʱ��������ȥ����ʾ��Ϣ
    if (pSystemTrayIcon->supportsMessages())
        pSystemTrayIcon->showMessage("SystemTrayIcon","Hi,This is my trayIcon",QSystemTrayIcon::Information,10000);

    pSystemTrayIcon->show();
}

GeneralMainWnd::~GeneralMainWnd()
{
    delete m_cornerPromptBox;
    delete ui;
}

// ���½ǵ���ʾ���ʹ��
void GeneralMainWnd::on_pushButtonCornerPromptBox_clicked()
{
    if (!m_cornerPromptBox)
        m_cornerPromptBox = new CornerPromptBox();

    //���ô�С
    m_cornerPromptBox->setFixedSize(300, 160);

    QString title;
    if (ui->radioButtonShowText->isChecked())
    {
        title = "��ʾ����";
        m_cornerPromptBox->setContent("������������ʽ��ʾ��ʾ���ݣ���");
    }
    else if (ui->radioButtonShowWidget->isChecked()) {
        title = "��ʾwidget";
        m_cornerPromptBox->setContent(new QLabel("������������ʽ��ʾ��ʾ���ݣ���"));
    }
    else
    {
        assert(0);
    }
    m_cornerPromptBox->setWindowTitle(title);

   // �����Ƿ�ֻ�ö�������
    m_cornerPromptBox->setUseAnimation( ui->checkBoxUsingAnimation->isChecked() );


    // ��ʾ����������ʾʱ��
    m_cornerPromptBox->showMsg(1000* ui->spinBoxSecond->value());
}

// ��װ�� diglog��ʹ��
void GeneralMainWnd::on_pushButtonShowDialog_clicked()
{
    int derection = 0;

    if (ui->radioButtonHengPai->isChecked())
    {
        derection = Qt::Horizontal;
    } else if (ui->radioButtonChuizhi->isChecked())
    {
        derection = Qt::Vertical;
    }

    // �������� �� ���岼��
    m_pDialog->setContent((new QLabel("��������κ� widget����")), derection);

//    disconnect(myObject, 0, this, 0);
    // ���� �� reject �� acceptǰ�������ź�
    connect(m_pDialog, SIGNAL(willReject(bool,bool&)),
            this, SLOT(slotWillReject(bool,bool&)) , Qt::UniqueConnection); //
    connect(m_pDialog, SIGNAL(willAccept(bool,bool&)),
            this, SLOT(slotWillAccept(bool,bool&)), Qt::UniqueConnection);

    connect(m_pDialog, SIGNAL(finished(int)),
            this, SLOT(slotDialogFinish(int)));

    m_pDialog->exec();
}

void GeneralMainWnd::slotWillReject(bool isModal, bool &reject)
{
    QMessageBox msgBox;

    msgBox.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    msgBox.setText( QString("model: %1 \n reject:%2").arg(isModal).arg(reject));
    msgBox.setWindowTitle(("reject ��"));

    int ret = msgBox.exec();
    if (ret == QMessageBox::Yes)
    {
        reject = true;
    }
    else if (ret == QMessageBox::No)
    {
        reject = false;
    }
}

void GeneralMainWnd::slotWillAccept(bool isModal, bool &accept)
{
    QMessageBox msgBox;

    msgBox.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    msgBox.setText( QString("model: %1 \n accept:%2").arg(isModal).arg(accept));
    msgBox.setWindowTitle(("accept �� "));

    int ret = msgBox.exec();
    if (ret == QMessageBox::Yes)
    {
        accept = true;
    }
    else if (ret == QMessageBox::No)
    {
        accept = false;
    }


//    disconnect(m_pDialog, SIGNAL(willAccept(bool,bool&)),
//               this, SLOT(slotWillAccept(bool,bool&)));
}

void GeneralMainWnd::slotDialogFinish(int result)
{
    if (result == QDialog::Accepted)
    {
        ui->labeldialogResult->setText("QDialog::Accepted");
    }
    else if (result == QDialog::Rejected)
    {
        ui->labeldialogResult->setText("QDialog::Rejected");
    }
}

void GeneralMainWnd::on_pushButtonGetComboBoxAllItemtext_clicked()
{
    QStringList l = qhGetComboBoxAllItemtext(ui->comboBoxEmpty);
    qDebug() << "ui->comboBoxEmpty item text";
    qDebug() << l;

    l = qhGetComboBoxAllItemtext(ui->comboBoxDisableEdit);
    qDebug() << "ui->comboBoxDisableEdit item text";
    qDebug() << l;

    l = qhGetComboBoxAllItemtext(ui->comboBoxEnableEdit);
    qDebug() << "ui->comboBoxEnableEdit item text";
    qDebug() << l;
}

void GeneralMainWnd::on_pushButtonSetComboBoxValue_clicked()
{
    QString text = ui->lineEditInHelpQComboBox->text();
    bool ret = qhSetComboBoxValue(ui->comboBoxEmpty, text);
    qDebug() << "qhSetComboBoxValue(ui->comboBoxEmpty, text)"
             << " text=" << text << " ret " << ret;
    ret = qhSetComboBoxValue(ui->comboBoxDisableEdit, text);
    qDebug() << "qhSetComboBoxValue(ui->comboBoxDisableEdit, text)"
             << " text=" << text << " ret " << ret;
    QH_VERIFY(qhSetComboBoxValue(ui->comboBoxEnableEdit, text));
}

void GeneralMainWnd::on_pushButtonDumpEventFilters_clicked()
{
    qhDumpEventFilters(this);

    QWidget *w = new QWidget();
    qDebug() << "qhDumpEventFilters(w)";
    qhDumpEventFilters(w);

    QWidget *c1 = new QWidget(w);
    c1->setObjectName("c1");
    w->installEventFilter(c1);
    qDebug() << "qhDumpEventFilters(w) after w->installEventFilter(c1);";
    qhDumpEventFilters(w);

    QWidget *c2 = new QWidget(w);
    c2->setObjectName("c2");
    w->installEventFilter(c2);


    QWidget *c3 = new QWidget(w);
    c3->setObjectName("c3");
    w->installEventFilter(c3);
    qDebug() << "qhDumpEventFilters(w) after w->installEventFilter(c3);";
//    qhDumpEventFilters(w);

    w->removeEventFilter(c2);
    qDebug() << "qhDumpEventFilters(w) after w->removeEventFilter(c2);";
//    qhDumpEventFilters(w);
}

void GeneralMainWnd::on_pushButtonDumpObjectTree_clicked()
{
    qhDumpObjectTree(this);
}

void GeneralMainWnd::on_pushButtonInitNote_clicked()
{
    QString file = QFileDialog::getOpenFileName(this,
                      tr("select ini file"),
                      QString(),
                      tr("All Files (*);;ini Files (*.ini)"));

    if (!file.isEmpty())
    {
        IniNote note;
        QH_VERIFY( note.getNoteFromIniFile(file) );
        QSettings setting(file,
                QSettings::IniFormat);
        //setting.setValue("12234", "value");
        setting.sync();
        QH_VERIFY( note.fillNoteToIniFile(file) );
    }
}

void GeneralMainWnd::on_pushButtonInitNoteRename_clicked()
{
    QString file = QFileDialog::getOpenFileName(this,
                      tr("select ini file"),
                      QString(),
                      tr("All Files (*);;ini Files (*.ini)"));

    if (!file.isEmpty())
    {
        IniNote note;
        QH_VERIFY( note.getNoteFromIniFile(file) );
        QSettings setting(file,
                QSettings::IniFormat);
        setting.setIniCodec( QTextCodec::codecForLocale() );
        setting.setValue("12234", "value");
        setting.sync();
        QH_VERIFY( note.fillNoteToIniFile(file, file+".ini") );
    }
}

void GeneralMainWnd::on_pushButtonShowDlg_clicked()
{
    int index = ui->comboBoxFileMode->currentIndex();
    int repeatMode = ui->comboBoxRepeatFileMode->currentIndex();

   // MulFileDialog::getOpenFileNames(this,)

    MulFileDialog fd(this, (QFileDialog::FileMode)index, tr("ѡ�����ļ����ļ���"));
    fd.setRepeatFilesMode((MulFileDialog::ERepeatFilesMode)repeatMode);
    if ( fd.exec() == QDialog::Accepted)
    {
        qDebug() << fd.getSelectedFiles();
    }
}
