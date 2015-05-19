#include "qhGui.h"



int qhFindStrInComboBox(const QComboBox* pComboBox, const QString &str)
{
    Q_ASSERT(pComboBox);
    int count = pComboBox->count();
    for (int i=0; i<count; i++)
    {
        if (pComboBox->itemText(i) == str)
        {
            return i;
        }
    }

    return -1;
}

QStringList qhGetComboBoxAllItemtext(const QComboBox* pComboBox)
{
    Q_ASSERT(pComboBox);

    QStringList list;
    int count = pComboBox->count();
    for (int i=0; i<count; i++)
    {
        list << pComboBox->itemText(i);
    }

    return list;
}

bool qhSetComboBoxValue(QComboBox* pComboBox, const QString &str)
{
//    int index = qhFindStrInComboBox(pComboBox, str);
    int index = pComboBox->findText(str);
    if (index == -1)
    {
        if (pComboBox->lineEdit())
        {
            pComboBox->setEditText(str);
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        pComboBox->setCurrentIndex(index);
        return true;
    }
}


void qhGetQTableWidgetAllItem(
        const QTableWidget *t,
        QList<QTableWidgetItem *> &list)
{
    Q_ASSERT(t);
    list.clear();
    int row = t->rowCount();
    int column = t->columnCount();

    for (int i=0; i<column; i++)
    {
        for (int j=0; j<row; j++)
        {
            list << t->item(j, i);
        }
    }
}
