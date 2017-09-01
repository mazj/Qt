#ifndef SITTINGWIDGET_H
#define SITTINGWIDGET_H

#include <QSharedDataPointer>
#include <QWidget>

class SittingWidgetData;

/*!
 * \brief 占位 widget
 * layout中一些有时需要插入一些 space 达到占位置的目的，从而使布局整齐。但这样的space大小伸缩因子之类的需要用户指定。有时挺麻烦。
 * 这个类的目的就是 在 layout占位置，这个widget的大小策略跟 targetWidget 一致
 * 注：在setTargetWidget（）时跟targetWidget的大小策略完全一致，若以后 targetWidget的大小策略变了，则需要重新调用 setTargetWidget（）
 */
class SittingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SittingWidget(QWidget *parent = 0);
    SittingWidget(const SittingWidget &);
    SittingWidget &operator=(const SittingWidget &);
    ~SittingWidget();

    void setTargetWidget(QWidget* pW);

    virtual QSize	sizeHint() const;

signals:

public slots:

private:
    QSharedDataPointer<SittingWidgetData> data;
};

#endif // SITTINGWIDGET_H
