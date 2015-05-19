/********************************************************************************
** Form generated from reading UI file 'HealthManMainWnd.ui'
**
** Created: Tue Sep 16 16:02:52 2014
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HEALTHMANMAINWND_H
#define UI_HEALTHMANMAINWND_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLCDNumber *lcdNumber;
    QSpacerItem *horizontalSpacer;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QRadioButton *fixTimeRadioButton;
    QRadioButton *processRunTimeRadioButton;
    QRadioButton *nowRadioButton;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(400, 300);
        verticalLayout_2 = new QVBoxLayout(Dialog);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        widget = new QWidget(Dialog);
        widget->setObjectName(QString::fromUtf8("widget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        lcdNumber = new QLCDNumber(widget);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
        QFont font;
        font.setFamily(QString::fromUtf8("Agency FB"));
        font.setBold(true);
        font.setWeight(75);
        lcdNumber->setFont(font);
        lcdNumber->setSmallDecimalPoint(false);
        lcdNumber->setNumDigits(8);
        lcdNumber->setMode(QLCDNumber::Dec);
        lcdNumber->setSegmentStyle(QLCDNumber::Flat);

        horizontalLayout->addWidget(lcdNumber);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout_2->addWidget(widget);

        groupBox = new QGroupBox(Dialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy1);
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        fixTimeRadioButton = new QRadioButton(groupBox);
        fixTimeRadioButton->setObjectName(QString::fromUtf8("fixTimeRadioButton"));
        fixTimeRadioButton->setChecked(false);

        verticalLayout->addWidget(fixTimeRadioButton);

        processRunTimeRadioButton = new QRadioButton(groupBox);
        processRunTimeRadioButton->setObjectName(QString::fromUtf8("processRunTimeRadioButton"));
        processRunTimeRadioButton->setChecked(true);

        verticalLayout->addWidget(processRunTimeRadioButton);

        nowRadioButton = new QRadioButton(groupBox);
        nowRadioButton->setObjectName(QString::fromUtf8("nowRadioButton"));

        verticalLayout->addWidget(nowRadioButton);


        verticalLayout_2->addWidget(groupBox);

        buttonBox = new QDialogButtonBox(Dialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_2->addWidget(buttonBox);


        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "\345\201\245\345\272\267 IT \344\272\272", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Dialog", "\350\267\235\347\246\273\344\274\221\346\201\257\346\227\266\351\227\264\350\277\230\346\234\211", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("Dialog", "\350\256\241\346\227\266\346\226\271\345\274\217\351\200\211\346\213\251", 0, QApplication::UnicodeUTF8));
        fixTimeRadioButton->setText(QApplication::translate("Dialog", "\344\273\216\345\233\272\345\256\232\346\227\266\351\227\264\347\202\271\345\274\200\345\247\213\350\256\260\346\227\266", 0, QApplication::UnicodeUTF8));
        processRunTimeRadioButton->setText(QApplication::translate("Dialog", "\344\273\216\347\250\213\345\272\217\345\274\200\345\247\213\350\277\220\350\241\214\345\274\200\345\247\213\350\256\241\346\227\266", 0, QApplication::UnicodeUTF8));
        nowRadioButton->setText(QApplication::translate("Dialog", "\344\273\216\347\216\260\345\234\250\345\274\200\345\247\213\350\256\241\346\227\266", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HEALTHMANMAINWND_H
