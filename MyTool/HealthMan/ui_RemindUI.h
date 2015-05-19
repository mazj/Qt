/********************************************************************************
** Form generated from reading UI file 'RemindUI.ui'
**
** Created: Tue Sep 16 16:02:52 2014
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REMINDUI_H
#define UI_REMINDUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RemindUI
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *delayPushButton;
    QPushButton *delayPushButton_2;
    QPushButton *delayPushButton_3;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *RemindUI)
    {
        if (RemindUI->objectName().isEmpty())
            RemindUI->setObjectName(QString::fromUtf8("RemindUI"));
        RemindUI->resize(640, 350);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(RemindUI->sizePolicy().hasHeightForWidth());
        RemindUI->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(RemindUI);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(RemindUI);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        QFont font;
        font.setFamily(QString::fromUtf8("Agency FB"));
        font.setPointSize(28);
        label->setFont(font);

        verticalLayout->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        delayPushButton = new QPushButton(RemindUI);
        delayPushButton->setObjectName(QString::fromUtf8("delayPushButton"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(delayPushButton->sizePolicy().hasHeightForWidth());
        delayPushButton->setSizePolicy(sizePolicy2);
        delayPushButton->setMinimumSize(QSize(121, 41));

        horizontalLayout->addWidget(delayPushButton);

        delayPushButton_2 = new QPushButton(RemindUI);
        delayPushButton_2->setObjectName(QString::fromUtf8("delayPushButton_2"));
        sizePolicy2.setHeightForWidth(delayPushButton_2->sizePolicy().hasHeightForWidth());
        delayPushButton_2->setSizePolicy(sizePolicy2);
        delayPushButton_2->setMinimumSize(QSize(121, 41));

        horizontalLayout->addWidget(delayPushButton_2);

        delayPushButton_3 = new QPushButton(RemindUI);
        delayPushButton_3->setObjectName(QString::fromUtf8("delayPushButton_3"));
        sizePolicy2.setHeightForWidth(delayPushButton_3->sizePolicy().hasHeightForWidth());
        delayPushButton_3->setSizePolicy(sizePolicy2);
        delayPushButton_3->setMinimumSize(QSize(121, 41));

        horizontalLayout->addWidget(delayPushButton_3);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(RemindUI);

        QMetaObject::connectSlotsByName(RemindUI);
    } // setupUi

    void retranslateUi(QWidget *RemindUI)
    {
        RemindUI->setWindowTitle(QApplication::translate("RemindUI", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("RemindUI", "\344\270\273\344\272\272\357\274\214\350\257\245\350\256\251\344\275\240\347\232\204\350\205\260\344\274\221\346\201\257 5 \345\210\206\351\222\237\344\272\206\345\223\246\357\274\201\357\274\201", 0, QApplication::UnicodeUTF8));
        delayPushButton->setText(QApplication::translate("RemindUI", "\345\273\266\350\277\237\344\274\221\346\201\257 5 \345\210\206\351\222\237", 0, QApplication::UnicodeUTF8));
        delayPushButton_2->setText(QApplication::translate("RemindUI", "\345\273\266\350\277\237\344\274\221\346\201\257 10 \345\210\206\351\222\237", 0, QApplication::UnicodeUTF8));
        delayPushButton_3->setText(QApplication::translate("RemindUI", "\345\273\266\350\277\237\344\274\221\346\201\257 15 \345\210\206\351\222\237", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class RemindUI: public Ui_RemindUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REMINDUI_H
