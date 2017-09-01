#include "SittingWidget.h"
#include <assert.h>
#include <QPointer>

class SittingWidgetData : public QSharedData
{
public:
    SittingWidgetData() {}

    QPointer<QWidget> pTargetWgt;

};

SittingWidget::SittingWidget(QWidget *parent)
    : QWidget(parent), data(new SittingWidgetData)
{

}

SittingWidget::SittingWidget(const SittingWidget &rhs) : data(rhs.data)
{

}

SittingWidget &SittingWidget::operator=(const SittingWidget &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

SittingWidget::~SittingWidget()
{

}

void SittingWidget::setTargetWidget(QWidget *pW)
{
    assert(pW);
    data->pTargetWgt = pW;

    if (data->pTargetWgt)
    {
        setMinimumSize( data->pTargetWgt->minimumSize() );
        setMaximumSize( data->pTargetWgt->maximumSize() );
        setSizePolicy( data->pTargetWgt->sizePolicy() );
    }
}

QSize SittingWidget::sizeHint() const
{
    if (data->pTargetWgt)
    {
        return data->pTargetWgt->sizeHint();
    }

    return QWidget::sizeHint();
}

