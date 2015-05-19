#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include <QListWidget>

class ListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit ListWidget(QWidget *parent = 0);
    
	inline virtual void doItemsLayout(){
        return QAbstractItemView::doItemsLayout();
    }

	void _update()
	{ QListWidget::doItemsLayout(); }
signals:

public slots:

};

#endif // LISTWIDGET_H
