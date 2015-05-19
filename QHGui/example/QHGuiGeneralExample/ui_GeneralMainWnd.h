/********************************************************************************
** Form generated from reading UI file 'GeneralMainWnd.ui'
**
** Created: Mon Jun 23 13:44:28 2014
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GENERALMAINWND_H
#define UI_GENERALMAINWND_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GeneralMainWnd
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_6;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpinBox *spinBoxSecond;
    QCheckBox *checkBoxUsingAnimation;
    QPushButton *pushButtonCornerPromptBox;
    QRadioButton *radioButtonShowText;
    QRadioButton *radioButtonShowWidget;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QRadioButton *radioButtonHengPai;
    QLabel *labeldialogResult;
    QRadioButton *radioButtonChuizhi;
    QPushButton *pushButtonShowDialog;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_3;
    QComboBox *comboBoxEmpty;
    QPushButton *pushButtonGetComboBoxAllItemtext;
    QComboBox *comboBoxDisableEdit;
    QLineEdit *lineEditInHelpQComboBox;
    QComboBox *comboBoxEnableEdit;
    QPushButton *pushButtonSetComboBoxValue;
    QGridLayout *gridLayout_5;
    QGroupBox *groupBox_5;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButtonInitNote;
    QPushButton *pushButtonInitNoteRename;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_4;
    QPushButton *pushButtonDumpEventFilters;
    QPushButton *pushButtonDumpObjectTree;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *GeneralMainWnd)
    {
        if (GeneralMainWnd->objectName().isEmpty())
            GeneralMainWnd->setObjectName(QString::fromUtf8("GeneralMainWnd"));
        GeneralMainWnd->resize(706, 440);
        centralWidget = new QWidget(GeneralMainWnd);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_6 = new QGridLayout(centralWidget);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        spinBoxSecond = new QSpinBox(groupBox);
        spinBoxSecond->setObjectName(QString::fromUtf8("spinBoxSecond"));
        spinBoxSecond->setValue(3);

        horizontalLayout->addWidget(spinBoxSecond);


        gridLayout->addLayout(horizontalLayout, 1, 1, 1, 1);

        checkBoxUsingAnimation = new QCheckBox(groupBox);
        checkBoxUsingAnimation->setObjectName(QString::fromUtf8("checkBoxUsingAnimation"));

        gridLayout->addWidget(checkBoxUsingAnimation, 0, 1, 1, 1);

        pushButtonCornerPromptBox = new QPushButton(groupBox);
        pushButtonCornerPromptBox->setObjectName(QString::fromUtf8("pushButtonCornerPromptBox"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButtonCornerPromptBox->sizePolicy().hasHeightForWidth());
        pushButtonCornerPromptBox->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pushButtonCornerPromptBox, 2, 0, 1, 1);

        radioButtonShowText = new QRadioButton(groupBox);
        radioButtonShowText->setObjectName(QString::fromUtf8("radioButtonShowText"));
        radioButtonShowText->setChecked(true);

        gridLayout->addWidget(radioButtonShowText, 0, 0, 1, 1);

        radioButtonShowWidget = new QRadioButton(groupBox);
        radioButtonShowWidget->setObjectName(QString::fromUtf8("radioButtonShowWidget"));

        gridLayout->addWidget(radioButtonShowWidget, 1, 0, 1, 1);


        gridLayout_6->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        radioButtonHengPai = new QRadioButton(groupBox_2);
        radioButtonHengPai->setObjectName(QString::fromUtf8("radioButtonHengPai"));
        radioButtonHengPai->setChecked(true);

        gridLayout_2->addWidget(radioButtonHengPai, 0, 0, 1, 1);

        labeldialogResult = new QLabel(groupBox_2);
        labeldialogResult->setObjectName(QString::fromUtf8("labeldialogResult"));

        gridLayout_2->addWidget(labeldialogResult, 0, 1, 2, 1);

        radioButtonChuizhi = new QRadioButton(groupBox_2);
        radioButtonChuizhi->setObjectName(QString::fromUtf8("radioButtonChuizhi"));

        gridLayout_2->addWidget(radioButtonChuizhi, 1, 0, 1, 1);

        pushButtonShowDialog = new QPushButton(groupBox_2);
        pushButtonShowDialog->setObjectName(QString::fromUtf8("pushButtonShowDialog"));
        sizePolicy.setHeightForWidth(pushButtonShowDialog->sizePolicy().hasHeightForWidth());
        pushButtonShowDialog->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(pushButtonShowDialog, 2, 0, 1, 1);


        gridLayout_6->addWidget(groupBox_2, 0, 1, 1, 1);

        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        gridLayout_3 = new QGridLayout(groupBox_3);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        comboBoxEmpty = new QComboBox(groupBox_3);
        comboBoxEmpty->setObjectName(QString::fromUtf8("comboBoxEmpty"));

        gridLayout_3->addWidget(comboBoxEmpty, 0, 0, 1, 1);

        pushButtonGetComboBoxAllItemtext = new QPushButton(groupBox_3);
        pushButtonGetComboBoxAllItemtext->setObjectName(QString::fromUtf8("pushButtonGetComboBoxAllItemtext"));

        gridLayout_3->addWidget(pushButtonGetComboBoxAllItemtext, 0, 1, 1, 1);

        comboBoxDisableEdit = new QComboBox(groupBox_3);
        comboBoxDisableEdit->setObjectName(QString::fromUtf8("comboBoxDisableEdit"));

        gridLayout_3->addWidget(comboBoxDisableEdit, 1, 0, 1, 1);

        lineEditInHelpQComboBox = new QLineEdit(groupBox_3);
        lineEditInHelpQComboBox->setObjectName(QString::fromUtf8("lineEditInHelpQComboBox"));

        gridLayout_3->addWidget(lineEditInHelpQComboBox, 1, 1, 1, 1);

        comboBoxEnableEdit = new QComboBox(groupBox_3);
        comboBoxEnableEdit->setObjectName(QString::fromUtf8("comboBoxEnableEdit"));
        comboBoxEnableEdit->setEditable(true);

        gridLayout_3->addWidget(comboBoxEnableEdit, 2, 0, 1, 1);

        pushButtonSetComboBoxValue = new QPushButton(groupBox_3);
        pushButtonSetComboBoxValue->setObjectName(QString::fromUtf8("pushButtonSetComboBoxValue"));

        gridLayout_3->addWidget(pushButtonSetComboBoxValue, 2, 1, 1, 1);


        gridLayout_6->addWidget(groupBox_3, 1, 0, 1, 1);

        gridLayout_5 = new QGridLayout();
        gridLayout_5->setSpacing(6);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        groupBox_5 = new QGroupBox(centralWidget);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        verticalLayout = new QVBoxLayout(groupBox_5);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        pushButtonInitNote = new QPushButton(groupBox_5);
        pushButtonInitNote->setObjectName(QString::fromUtf8("pushButtonInitNote"));

        verticalLayout->addWidget(pushButtonInitNote);

        pushButtonInitNoteRename = new QPushButton(groupBox_5);
        pushButtonInitNoteRename->setObjectName(QString::fromUtf8("pushButtonInitNoteRename"));

        verticalLayout->addWidget(pushButtonInitNoteRename);


        gridLayout_5->addWidget(groupBox_5, 0, 0, 1, 1);

        groupBox_4 = new QGroupBox(centralWidget);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        gridLayout_4 = new QGridLayout(groupBox_4);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        pushButtonDumpEventFilters = new QPushButton(groupBox_4);
        pushButtonDumpEventFilters->setObjectName(QString::fromUtf8("pushButtonDumpEventFilters"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButtonDumpEventFilters->sizePolicy().hasHeightForWidth());
        pushButtonDumpEventFilters->setSizePolicy(sizePolicy1);

        gridLayout_4->addWidget(pushButtonDumpEventFilters, 0, 0, 1, 1);

        pushButtonDumpObjectTree = new QPushButton(groupBox_4);
        pushButtonDumpObjectTree->setObjectName(QString::fromUtf8("pushButtonDumpObjectTree"));
        sizePolicy1.setHeightForWidth(pushButtonDumpObjectTree->sizePolicy().hasHeightForWidth());
        pushButtonDumpObjectTree->setSizePolicy(sizePolicy1);

        gridLayout_4->addWidget(pushButtonDumpObjectTree, 1, 0, 1, 1);


        gridLayout_5->addWidget(groupBox_4, 0, 1, 1, 1);


        gridLayout_6->addLayout(gridLayout_5, 1, 1, 1, 1);

        GeneralMainWnd->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(GeneralMainWnd);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 706, 23));
        GeneralMainWnd->setMenuBar(menuBar);
        mainToolBar = new QToolBar(GeneralMainWnd);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        GeneralMainWnd->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(GeneralMainWnd);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        GeneralMainWnd->setStatusBar(statusBar);

        retranslateUi(GeneralMainWnd);

        QMetaObject::connectSlotsByName(GeneralMainWnd);
    } // setupUi

    void retranslateUi(QMainWindow *GeneralMainWnd)
    {
        GeneralMainWnd->setWindowTitle(QApplication::translate("GeneralMainWnd", "GeneralMainWnd", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("GeneralMainWnd", "\345\217\263\344\270\213\350\247\222\347\232\204\346\217\220\347\244\272\346\241\206CornerPromptBox \347\232\204\344\275\277\347\224\250", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("GeneralMainWnd", "\346\227\266\351\227\264 \347\247\222", 0, QApplication::UnicodeUTF8));
        checkBoxUsingAnimation->setText(QApplication::translate("GeneralMainWnd", "\347\224\250\345\212\250\347\224\273", 0, QApplication::UnicodeUTF8));
        pushButtonCornerPromptBox->setText(QApplication::translate("GeneralMainWnd", "\346\230\276\347\244\272", 0, QApplication::UnicodeUTF8));
        radioButtonShowText->setText(QApplication::translate("GeneralMainWnd", "\346\230\276\347\244\272\346\226\207\345\255\227", 0, QApplication::UnicodeUTF8));
        radioButtonShowWidget->setText(QApplication::translate("GeneralMainWnd", "\346\230\276\347\244\272widget", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("GeneralMainWnd", "\350\207\252\345\267\261\345\260\201\350\243\205\347\232\204Diglog\347\232\204\344\275\277\347\224\250", 0, QApplication::UnicodeUTF8));
        radioButtonHengPai->setText(QApplication::translate("GeneralMainWnd", "\346\260\264\345\271\263\345\270\203\345\261\200", 0, QApplication::UnicodeUTF8));
        labeldialogResult->setText(QApplication::translate("GeneralMainWnd", "TextLabel", 0, QApplication::UnicodeUTF8));
        radioButtonChuizhi->setText(QApplication::translate("GeneralMainWnd", "\345\236\202\347\233\264\345\270\203\345\261\200", 0, QApplication::UnicodeUTF8));
        pushButtonShowDialog->setText(QApplication::translate("GeneralMainWnd", "\346\230\276\347\244\272", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("GeneralMainWnd", "HelpQComboBox \347\233\270\345\205\263\345\207\275\346\225\260", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushButtonGetComboBoxAllItemtext->setToolTip(QApplication::translate("GeneralMainWnd", "qhGetComboBoxAllItemtext", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButtonGetComboBoxAllItemtext->setText(QApplication::translate("GeneralMainWnd", "qhGetComboBoxAllItemtext", 0, QApplication::UnicodeUTF8));
        comboBoxDisableEdit->clear();
        comboBoxDisableEdit->insertItems(0, QStringList()
         << QApplication::translate("GeneralMainWnd", "1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GeneralMainWnd", "abc", 0, QApplication::UnicodeUTF8)
        );
        comboBoxEnableEdit->clear();
        comboBoxEnableEdit->insertItems(0, QStringList()
         << QApplication::translate("GeneralMainWnd", "1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GeneralMainWnd", "abc", 0, QApplication::UnicodeUTF8)
        );
#ifndef QT_NO_TOOLTIP
        pushButtonSetComboBoxValue->setToolTip(QApplication::translate("GeneralMainWnd", "qhSetComboBoxValue", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButtonSetComboBoxValue->setText(QApplication::translate("GeneralMainWnd", "qhSetComboBoxValue", 0, QApplication::UnicodeUTF8));
        groupBox_5->setTitle(QApplication::translate("GeneralMainWnd", "InitNote", 0, QApplication::UnicodeUTF8));
        pushButtonInitNote->setText(QApplication::translate("GeneralMainWnd", "InitNote", 0, QApplication::UnicodeUTF8));
        pushButtonInitNoteRename->setText(QApplication::translate("GeneralMainWnd", "InitNoteRename", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("GeneralMainWnd", "Dump ", 0, QApplication::UnicodeUTF8));
        pushButtonDumpEventFilters->setText(QApplication::translate("GeneralMainWnd", "qhDumpEventFilters", 0, QApplication::UnicodeUTF8));
        pushButtonDumpObjectTree->setText(QApplication::translate("GeneralMainWnd", "qhDumpObjectTree", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class GeneralMainWnd: public Ui_GeneralMainWnd {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GENERALMAINWND_H
