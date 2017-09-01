#ifndef LABELBUTTON_H
#define LABELBUTTON_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>


namespace Ui {
	class LabelButton;
}
class QToolButton;
class SoProductInfo;
class SoThink;

class ButtonWithMark : public QPushButton
{
	Q_OBJECT

public:
	explicit ButtonWithMark(QWidget *parent = 0);
	~ButtonWithMark();
	void setProductInfo(const SoProductInfo* p);

public slots:
	void updateProductInfo();

protected:
	void resizeEvent(QResizeEvent *event);
	void mouseMoveEvent(QMouseEvent * e);
	void leaveEvent(QEvent * event);
	void enterEvent(QEvent * event);
	QSize	sizeHint() const;

private:
	//Ui::LabelButton *ui;
	//QToolButton *m_pCornerButton;

	QPointer<QPushButton> m_pCornerButton;
	QPointer<QLabel> m_pStatuLabel;
	const SoProductInfo* m_pProductInfo;
};

class LabelButton : public QWidget
{
	Q_OBJECT

public:
	explicit LabelButton(QWidget *parent = 0);
	~LabelButton();
	
	void setProductInfo(SoThink *pSo, const SoProductInfo* p);
	void updateProductInfo();
	void setLabelText(const QString& str);
	QLabel* label();
	QPushButton *button();
	//QPushButton *cornerButton();
	void hideSitting(); //让该控件在 layout还占据空间，但不显示，就跟没有该控件似的
	//protected:
	//   void resizeEvent();

signals:
	void sigBuyProduct();
    void sigStartSubProduct( int appType );

private slots:
	void on_pushButton_clicked();
	void onCornerButtonClick();

protected:
	//QSize	sizeHint() const;

private:
	Ui::LabelButton *ui;
	//QToolButton
	const SoProductInfo* m_pProductInfo;
};

#endif // LABELBUTTON_H
