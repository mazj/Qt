#include "SittingWidget.h"

class SittingWidgetData : public QSharedData
{
public:

};

SittingWidget::SittingWidget(QWidget *parent) : QWidget(parent), data(new SittingWidgetData)
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

