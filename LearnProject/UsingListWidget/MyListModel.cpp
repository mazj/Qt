#include "MyListModel.h"

MyListModel::MyListModel(QObject *parent) :
    QAbstractListModel(parent)
{
    mVector.reserve(20000);
}

QVariant MyListModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        int row = index.row();
        if ((unsigned int)row < mVector.size() && row >= 0)
        {
            return mVector[row];
        }
        else
        {
            qWarning("index.row out range");
            return QVariant();
        }
    }
    else
    {
		return QVariant();
        //return QAbstractListModel::data(index, role);
    }
}
