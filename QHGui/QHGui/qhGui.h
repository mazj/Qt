#ifndef QHGUI_H
#define QHGUI_H

#include "HelpObject.h"

class QComboBox;
class QTableWidgetItem;
class QTableWidget;

/**
 * ��ӡ obj ���¼����������� qDebug ��ӡ
 * @param obj
 */
inline void qhDumpEventFilters(const QObject *obj)
{ return HelpObject::dumpEventFilters(obj); }

/**
 * �� HelpObject::_dumpObjectTree(obj)
 */
inline void qhDumpObjectTree(const QObject *obj)
{ return HelpObject::_dumpObjectTree(obj); }

/**
 * �� QComboBox ���� text �� str �� item�� ��������ֵ,û�ҵ����� -1
 * \note  QComboBox �в��ҵĺ��� int QComboBox::findText��������QComboBox::findText����
 * @param str
 * @return
 * \test HelpQComboBox
 */
int qhFindStrInComboBox(const QComboBox* pComboBox, const QString &str);

/**
 * �õ� QComboBox ������ Itemtext, ���ص� QStringList�е� �ַ���˳���� QComboBox�ı�ѡ��˳������
 * @return
 * \test HelpQComboBox
 */
QStringList qhGetComboBoxAllItemtext(const QComboBox* pComboBox);

/**
 * @brief ���� ComboBox ��ֵ, ���سɹ����
 *
 * �� QComboBox �Ѿ������˸��ַ���str����Ѹ��ַ������óɵ�ǰ�ַ�����������
 * �� QComboBox �Ѿ������и��ַ���str����QComboBox�ɱ༭��Ѱѱ༭���ڵ��������ó�
 *  str�������棻��QComboBox���ɱ༭���ؼ١�
 * ��֮���ڲ��ı� QComboBox ��ѡ������������ ��ǰ��ʾ���ַ���
 * @param pComboBox
 * @param str
 *
 * \test HelpQComboBox
 */
bool qhSetComboBoxValue(QComboBox* pComboBox, const QString &str);

/**
* @brief �ھ������ı� QComboBox �ĵ�ǰ�ַ�����ǰ���£����� QComboBox�ı�ѡ�ַ���

* 1.�Ȼ�ȡ QComboBox �ĵ�ǰ�ַ��� x��Ȼ�����QComboBox�����еı�ѡ�ַ������ٰ� QComboBox
* ��ѡ�ַ��� ���ó� strList��
* 2. �� strList ���� x����� QComboBox �ĵ�ǰ�ַ��� ���ó� x �������档
*    �� strList ������ x����� QComboBox �ĵ�ǰ�ַ��� ���ó�strList[0] �����ؼ١�
* @param pComboBox
* @param strList
* \test HelpQComboBox
*/
bool qhSetComboBoxItems(QComboBox* pComboBox, const QStringList &strList);

/**
 * �õ� QTableWidget ������ QTableWidgetItem
 * @param t
 * @param list
 ** \test HelpQTableWidget
 */
void qhGetQTableWidgetAllItem(
        const QTableWidget *t,
        QList<QTableWidgetItem *> &list);

/**
 * @brief qhGetQTableWidgetAllItem ���غ���
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
* @brief ɾ�� QTableWidget ������
* @param t
* @return
* \test HelpQTableWidget
*/
void qhRemoveQTableWidgetAllRow(QTableWidget *t);


#endif // QHGUI_H
