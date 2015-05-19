#ifndef MYLISTMODEL_H
#define MYLISTMODEL_H

#include <List>
#include <Vector>
#include <QAbstractListModel>
#include <QObject>
#include <QString>

class MyListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit MyListModel(QObject *parent = 0);
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

//signals:

//public slots:

private:
//    std::list mList;
    std::vector<QString> mVector;
};

#endif // MYLISTMODEL_H
