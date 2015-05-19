#ifndef QHGUI_H
#define QHGUI_H

#include "HelpObject.h"

class QComboBox;
class QTableWidgetItem;
class QTableWidget;

/**
 * 打印 obj 的事件过滤器，用 qDebug 打印
 * @param obj
 */
inline void qhDumpEventFilters(const QObject *obj)
{ return HelpObject::dumpEventFilters(obj); }

/**
 * 见 HelpObject::_dumpObjectTree(obj)
 */
inline void qhDumpObjectTree(const QObject *obj)
{ return HelpObject::_dumpObjectTree(obj); }

/**
 * 在 QComboBox 查找 text 是 str 的 item， 返回索引值,没找到返回 -1
 * \note  QComboBox 有查找的函数 int QComboBox::findText（），用QComboBox::findText更好
 * @param str
 * @return
 * \test HelpQComboBox
 */
int qhFindStrInComboBox(const QComboBox* pComboBox, const QString &str);

/**
 * 得到 QComboBox 的所有 Itemtext, 返回的 QStringList中的 字符串顺序按照 QComboBox的备选项顺序排列
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
* @brief 在尽量不改变 QComboBox 的当前字符串的前提下，设置 QComboBox的备选字符串

* 1.先获取 QComboBox 的当前字符串 x，然后清空QComboBox的所有的备选字符串，再把 QComboBox
* 备选字符串 设置成 strList。
* 2. 若 strList 含有 x，则把 QComboBox 的当前字符串 设置成 x 并返回真。
*    若 strList 不含有 x，则把 QComboBox 的当前字符串 设置成strList[0] 并返回假。
* @param pComboBox
* @param strList
* \test HelpQComboBox
*/
bool qhSetComboBoxItems(QComboBox* pComboBox, const QStringList &strList);

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

/**
* @brief 删除 QTableWidget 所有行
* @param t
* @return
* \test HelpQTableWidget
*/
void qhRemoveQTableWidgetAllRow(QTableWidget *t);


#endif // QHGUI_H
