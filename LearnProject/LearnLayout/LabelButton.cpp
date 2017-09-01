#include "stdafx.h"
#include "LabelButton.h"
#include "ui_LabelButton.h"
#include "SoThink.h"

#include <QtWidgets/QToolButton>
//#include <QtCore/QResizeEvent>

const static int ButtonWithMarkDufaultWidth = 80;
const static int ButtonWithMarkDufaultHeight = 80;

ButtonWithMark::ButtonWithMark(QWidget *parent)
: QPushButton(parent),
m_pProductInfo(NULL)
{
	m_pCornerButton = new QPushButton( QString(""), this);
	m_pCornerButton->setObjectName( QString("corner") );
	//m_pCornerButton->move(0, 0);
	m_pCornerButton->setGeometry(0, 0, 26, 22);
	connect(m_pCornerButton, SIGNAL(clicked()), parent, SLOT(onCornerButtonClick()));
	m_pCornerButton->hide();

	m_pStatuLabel = new QLabel( QString("statuLabel"), this );
	m_pStatuLabel->setObjectName( QString("statuLabel") );
	m_pStatuLabel->setAlignment(Qt::AlignCenter);

	//setMinimumSize(ButtonWithMarkDufaultWidth, ButtonWithMarkDufaultHeight);
	setFixedSize(ButtonWithMarkDufaultWidth, ButtonWithMarkDufaultHeight);

	//setStyleSheet(QString( "ButtonWithMark { order:2px groove gray;"
	//	"border-radius:10px;"
	//	"padding:2px 4px; }") );

}

ButtonWithMark::~ButtonWithMark()
{

}

void ButtonWithMark::setProductInfo( const SoProductInfo* p )
{
	m_pProductInfo = p;
}


void ButtonWithMark::updateProductInfo()
{
	if (m_pProductInfo) 
	{
		switch(m_pProductInfo->status)
		{
		case SoProductStatus_Normal:
			m_pStatuLabel->setText(QString(""));
			break;
		case SoProductStatus_Trial:
			//m_pStatuLabel->setStyleSheet("color: black");
			m_pStatuLabel->setStyleSheet("color: red");
			m_pStatuLabel->setText(tr("Trial"));
			break;
		case SoProductStatus_Expired:
			m_pStatuLabel->setStyleSheet("color: red");
			m_pStatuLabel->setText(tr("Expired"));
			break;
		case SoProductStatus_UnKnown:
			assert(0);
			m_pStatuLabel->setText(QString("UnKnown"));
			break;
		default:
			assert(0);
		}
	}
}



void ButtonWithMark::resizeEvent( QResizeEvent * event )
{
	int h = event->size().height();
	int w = event->size().width();

	//if (m_pCornerButton)
		//m_pCornerButton->resize(event->size() / 3);

	if (m_pStatuLabel)
		m_pStatuLabel->setGeometry(0, h * 3 / 4, w, h * 1 / 4);

	//foreach (QObject* pChild, children()) {
	//	QPushButton *pBtn = qobject_cast<QPushButton*>(pChild);
	//	if (pBtn)
	//	{
	//		pBtn->resize(event->size() / 3);
	//		//break;
	//	}

	//	QLabel *pLab = qobject_cast<QLabel*>(pChild);
	//	if (pLab)
	//	{
	//		int h = event->size().height();
	//		int w = event->size().width();
	//		pLab->setGeometry(0, h * 3 / 4, w, h * 1 / 4);
	//		//break;
	//	}
	//}
}

void ButtonWithMark::mouseMoveEvent(QMouseEvent * e)
{
	QPushButton::mouseMoveEvent(e);
}

QSize ButtonWithMark::sizeHint() const
{
	//return QPushButton::sizeHint();
	return QSize(ButtonWithMarkDufaultWidth, ButtonWithMarkDufaultHeight);
}

void ButtonWithMark::leaveEvent( QEvent * event )
{
	if (m_pProductInfo)
	{
		if (m_pCornerButton->isVisible())
			m_pCornerButton->hide();
	}

	QPushButton::leaveEvent(event);
}

void ButtonWithMark::enterEvent( QEvent * event )
{
	if (m_pProductInfo)
	{
		if (m_pProductInfo->status != SoProductStatus_Normal)
		{
			//m_pCornerButton->move(width()/2-m_pCornerButton->width()/2, height()/2-m_pCornerButton->height()/2);
			m_pCornerButton->move(0, height()/2-m_pCornerButton->height()/2);
			m_pCornerButton->show();
		}
	}

	QPushButton::enterEvent(event);
}

LabelButton::LabelButton(QWidget *parent) :
QWidget(parent),
ui(new Ui::LabelButton),
m_pProductInfo(NULL)
{
	ui->setupUi(this);

	//ui->pushButton->setIcon(QIcon(":/images/images/BUTTON.png"));
	//QIcon(":/images/images/key_down.png"),



}

LabelButton::~LabelButton()
{
	delete ui;
}


void LabelButton::setProductInfo( SoThink *pSo, const SoProductInfo* p )
{
	m_pProductInfo = p;
	ui->pushButton->setProductInfo(p);

	connect(pSo, SIGNAL(sigUpdateProductInfo()), ui->pushButton, SLOT(updateProductInfo()));
}

void LabelButton::updateProductInfo()
{
	ui->pushButton->updateProductInfo();
}

void LabelButton::setLabelText( const QString& str )
{
	ui->label->setText(str);
}

QLabel* LabelButton::label()
{
	return ui->label;
}

QPushButton * LabelButton::button()
{
	return ui->pushButton;
}

//QPushButton * LabelButton::cornerButton()
//{
//	
//}


void LabelButton::hideSitting()
{
	ui->label->setText(QString(""));
	ui->pushButton->setText(QString(""));
	ui->pushButton->deleteLater();
	//m_pCornerButton->setDisabled(true);
	//transparent

	QWidget *pW = new QWidget();
	pW->setFixedSize(ButtonWithMarkDufaultWidth, ButtonWithMarkDufaultHeight);
	ui->verticalLayout->insertWidget(0, pW );
}


void LabelButton::on_pushButton_clicked()
{
    emit sigStartSubProduct( m_pProductInfo->appType );
}

void LabelButton::onCornerButtonClick()
{
	emit sigBuyProduct();
}






