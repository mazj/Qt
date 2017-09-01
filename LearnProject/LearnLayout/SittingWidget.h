#ifndef SITTINGWIDGET_H
#define SITTINGWIDGET_H

#include <QSharedDataPointer>
#include <QWidget>

class SittingWidgetData;

class SittingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SittingWidget(QWidget *parent = 0);
    SittingWidget(const SittingWidget &);
    SittingWidget &operator=(const SittingWidget &);
    ~SittingWidget();

signals:

public slots:

private:
    QSharedDataPointer<SittingWidgetData> data;
};

#endif // SITTINGWIDGET_H
