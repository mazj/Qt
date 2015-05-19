#include "Dialog.h"
#include <QBoxLayout>
#include <QDialogButtonBox>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    m_reject(true),
    m_accept(true)
{
    QHBoxLayout *pLayout = new QHBoxLayout();
    pLayout->setSpacing(0);
    pLayout->setContentsMargins(0, 0, 0, 0);

    m_pCentreWidget = new QWidget();
    pLayout->addWidget(m_pCentreWidget);

    setLayout(pLayout);
}

/**
  ���öԻ�������
 * @param content
 * @param layouOrientation ���ַ���ȡQt::Horizontal	0x1 �� Qt::Vertical
 */
bool Dialog::setContent(QWidget *content, int layoutOrientation)
{
    bool ret = false;
    Q_ASSERT(content);
    // �����ϴεĽ���
    layout()->removeWidget(m_pCentreWidget);
    m_pCentreWidget->deleteLater();
    m_pCentreWidget = new QWidget();
    layout()->addWidget(m_pCentreWidget);

    if (layoutOrientation == Qt::Horizontal)
    {
        QBoxLayout *pLayout = new QHBoxLayout();
        pLayout->setMargin(3);

        pLayout->addWidget(content);

        QDialogButtonBox *buttonBox = new QDialogButtonBox();
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        QObject::connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

        pLayout->addWidget(buttonBox);
        QHBoxLayout *p = new QHBoxLayout();
        p->addWidget(new QDialog(content));
        pLayout->addLayout(p);


        m_pCentreWidget->setLayout(pLayout);
        ret = true;
    }

    else if (layoutOrientation == Qt::Vertical)
    {
        QBoxLayout *pLayout = new QVBoxLayout();
        pLayout->setMargin(3);

        pLayout->addWidget(content);

        QDialogButtonBox *buttonBox = new QDialogButtonBox();
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        QObject::connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

        pLayout->addWidget(buttonBox);

        m_pCentreWidget->setLayout(pLayout);
        ret = true;
    }
    else
    {
        Q_ASSERT_X(0, "", "���� orientation ����");
    }

//    dumpObjectTree();
    return ret;
}

#if 1
/**
 * ��Qdialog �ĵ�˵ reject() �� accept()��ֻ�� Modal ������ ���ã�
 *���� ����ʵ�ֵ������麯�����������κ������ʹ��
 */
void Dialog::accept()
{
    bool m = isModal();
    emit willAccept(m, m_accept);
    if (!m_accept)
        return;

    if (m)
    {
        QDialog::accept();
    }
    else
    {
        setResult(Accepted);

        emit finished(Accepted);
        emit accepted();
    }
}

void Dialog::reject()
{
    bool m = isModal();
    emit willReject(m, m_reject);
    if (!m_reject)
        return;

    if (m)
    {
        QDialog::reject();
    }
    else
    {
        setResult(Rejected);

        emit finished(Rejected);
        emit rejected();
    }
}
#endif
