#ifndef QHGUI_H
#define QHGUI_H

#include <string.h>
#include <QtGlobal>
#include <QObject>
#include <QPointer>
#include <QStringList>
#include <QList>
#include <QMap>

class QComboBox;
class QTableWidgetItem;
class QTableWidget;

/**
 * 在 QComboBox 查找 text 是 str 的 item， 返回索引值,没找到返回 -1
 * \note  QComboBox 有查找的函数 int QComboBox::findText（），用QComboBox::findText更好
 * @param str
 * @return
 * \test HelpQComboBox
 */
int qhFindStrInComboBox(const QComboBox* pComboBox, const QString &str);

/**
 * 得到 QComboBox 的所有 Itemtext
 * @return
 * \test HelpQComboBox
 */
QStringList qhGetComboBoxAllItemtext(const QComboBox* pComboBox);

/**
 * @brief 设置 ComboBox 的值, 返回成功与否
 *
 * 若 QComboBox 已经含有了该字符串str，则把该字符串设置成当前字符串，返回真
 * 若 QComboBox 已经不含有该字符串str，若QComboBox可编辑则把把编辑框内的文字设置成
 *  str，返回真；若QComboBox不可编辑返回假。
 * 总之，在不改变 QComboBox 备选项的情况下设置 当前显示的字符串
 * @param pComboBox
 * @param str
 *
 * \test HelpQComboBox
 */

bool qhSetComboBoxValue(QComboBox* pComboBox, const QString &str);

/**
 * 得到 QTableWidget 的所有 QTableWidgetItem
 * @param t
 * @param list
 ** \test HelpQTableWidget
 */
void qhGetQTableWidgetAllItem(
        const QTableWidget *t,
        QList<QTableWidgetItem *> &list);

/**
 * @brief qhGetQTableWidgetAllItem 重载函数
 * @param t
 * @return
 */
inline QList<QTableWidgetItem *> qhGetQTableWidgetAllItem(const QTableWidget *t)
{
    QList<QTableWidgetItem *> list;
    qhGetQTableWidgetAllItem(t, list);
    return list;
}

#endif // QHGUI_H
