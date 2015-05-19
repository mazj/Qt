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
 * �� QComboBox ���� text �� str �� item�� ��������ֵ,û�ҵ����� -1
 * \note  QComboBox �в��ҵĺ��� int QComboBox::findText��������QComboBox::findText����
 * @param str
 * @return
 * \test HelpQComboBox
 */
int qhFindStrInComboBox(const QComboBox* pComboBox, const QString &str);

/**
 * �õ� QComboBox ������ Itemtext
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

#endif // QHGUI_H
