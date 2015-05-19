/**
  \file qhXml.h
  \brief ��װ qt�й��� xml��һЩ������qt�İ���������qh��ͷ

  \note Ϊ�˲���һ���ض������������ң� ÿ������������ һ�� \\test ��ǩ��һ�������Ϊ Help�ؼ�
  \test Ϊ�˲���һ���ض������������ң� ÿ������������ һ�� \\test ��ǩ��һ�������Ϊ Help�ؼ�
  \author �ﺣ��
  \date 2014.10.17  ����
  */

#ifndef QHXML_H
#define QHXML_H

#include <string.h>
#include <QtGlobal>
#include <QObject>
#include <QPointer>
#include <QStringList>
#include <QList>
#include <QMap>
#include <QTime>
#include <QSettings>

#include "QHToolGlobal.h"

class QDomElement;
class QDomText;

/**
 * @brief qhDomFindElement
  �ҵ� �ڵ� e�ĵ�һ����������������ڵ㣬��
<first>firstText
    <second>
        <third>thirdtext1</third>
        <third>thirdtext2</third>
    </second>
    <second>
        <third>thirdtext3</third>
        <third>thirdtext4</third>
    </second>
</first>
�� e���� first�ڵ㣬childLst�������� secong third���򷵻� �ڵ� <third>thirdtext1</third>
 * @param e
 * @param childLst
 * @return
 *\test HelpQDomElement
 */
QDomElement qhDomFindElement(const QDomElement& _e, const QList<QString>& childLst);

/**
 * @brief qhDomFindElements
 *  �ҵ� �ڵ� e��������������������ڵ㣬��
<first>firstText
    <second>
        <third>thirdtext1</third>
        <third>thirdtext2</third>
    </second>
    <second>
        <third>thirdtext3</third>
        <third>thirdtext4</third>
    </second>
</first>
��ô e���� first�ڵ㣬childLst�������� secong third��
�򷵻� �ڵ� <third>thirdtext1</third> <third>thirdtext2</third> <third>thirdtext3</third> <third>thirdtext4</third>

 * @param e
 * @param childLst
 * @return
 *\test HelpQDomElement
 */
QList<QDomElement> qhDomFindElements(const QDomElement& _e, QList<QString> childLst);

/**
 * @brief qhDomFindElement
 *  ���� tagName�� tagName������ֵ�� attributes��һ���ӽڵ�
 * @param _e
 * @param tagName Ϊ���� ���ж�tagName
 * @param attributes
 * @return
 */
QDomElement qhDomFindElement(const QDomElement& _e, const QString &tagName,
                             const QMap<QString, QString>& attributes);

/**
 * @brief �ҵ� QDomElement  _e �� QDomText ���͵��ӽڵ㣬�ӽڵ������Ҫ�� text
 * @param _e
 * @param text
 * @return
 *\test HelpQDomElement
 */
QDomText qhDomFindText(const QDomElement& _e, const QString& text);

/**
 * @brief getQSettingsXmlFormat
 * QSettings Ĭ�ϲ�֧���� xml��ʽ����������Ϣ����Ҫ�û�����ע�ᴦ�� ����xml��ʽ�ĺ���.
 *
 * ������ xml ��ʽ���� QSettings ��Ϣ �� ����xml�淶�Ļ���������Щ���ơ������������
 <dido_config_table QSXmlData="my data">
    <version>1.0</version>
    <device>
        <commonDevice>
            <di>
                <board_type_1>
                    <NULL></NULL>
                    <a02>0</a02>
                    <a04>1</a04>
                </board_type_1>
            </di>
        </commonDevice>
    </device>
    <logins>
        <QSXmlArray Index="1">
          <userName QSXmlData="name1"/>
        </QSXmlArray>
        <QSXmlArray Index="2">
          <userName QSXmlData="name2"/>
        </QSXmlArray>
        <size QSXmlData="2"/>
    </logins>
</dido_config_table>

1.�ڵ�����Ҫ���� xml�淶����ڵ����Ʋ����� �����ֿ�ͷ���ַ�������1����/1����.
 ������ xml�淶ǰ����
    <1>�ڵ������в��ܳ��� б�ܺͷ�б�ܣ�QSettings ���ƣ�
    <2>���� QSXmlData ��Ϊ�� QSetting��key��ֵ
    <3> tagName �� QSXmlArray�İ��� QSetting�Ķ��г�Ա�������� Index��ֵ�Ƕ��г�Ա������ֵ��
        tagName Ϊsize�Ľڵ��ֵ�� �� QSetting����Ϊ�Ƕ��еĴ�С��

2.ͬһ���Ľڵ����Ʋ���ͬ������
<dido_config_table>
    <a02>0</a02>
    <a02>1</a02>
</dido_config_table>
������
3. QSettings �� key �� xml�Ľڵ�·����Ӧ���� dido_config_table/device/commonDevice/di/board_type_1/_1
��Ӧ�ڵ� <_1>255</_1>��
keyֵ��Ӧ��value����
��1���� key��Ӧ�Ľڵ���ֵ����valueΪ��Ӧ��ֵ���� <_1>255</_1>
��2����key��Ӧ�Ľڵ���ֵ����:
        �� �ýڵ�������� QSXmlData���� ����QSXmlData��ֵΪkey��value
4.ͬһ���Ľڵ��keyֵ û���Ⱥ�˳��֮�֣� ���� QSettings һ��
5.ֻ����ڵ������� QSXmlData Index.
6.�սڵ���Ϊ���� QSettings �� key���� <NULL></NULL>
 * @param encode    �����ļ�ʱ�ı��뷽ʽ��ֻ�ڱ���xml�����ļ�ʱ��Ч
* @return QSettings::Format,������ֵ �� QSettings::IniFormat ����Ч
 *  \test HelpQSettings
 */
QSettings::Format qhGetQSettingsXmlFormat(EQHEncode encode = EQHEncodeUTF8);
const int QSettingsIntLength = 4;

/**
 * �ж��ǲ��Ǳ�׼�� QSettingsXmlFormat ��ʽ���ļ�
 * @param file
 * @return
 */
bool qhIsQSettingsXmlFormatFile(const QString& file, QString& errInfo);

/**
 * @brief �ַ���ת���� csv��ʽ���ַ���
 * @param xmlstring
 * @return
 */
inline QString qhStr2CSV(const QString &xmlstring)
{
    QString string(xmlstring);
    string.replace("\"", "\"\"");
    string.prepend('"');
    string.push_back('"');
    return string;
}

/**
 * @brief �ַ���ת���� csv��ʽ���ַ���,������ excel �Դ� csv�ļ�ʱ�Ĵ���
 *
 * csv  ��ת���� xls��ʽʱ���� һ����Ԫ����ַ����� +��-��ͷ��excel����Ϊ�Ǻ�������Ԫ��ͷ��+��-��excel����������)��
 * Ϊ������һ�㣬�� +��-ǰ�Ӹ��ո񼴿�
 * @param xmlstring
 * @return
 */
inline QString qhStr2CSVWithExcel(const QString &xmlstring)
{
    QString string(xmlstring);
    string.replace("\"", "\"\"");
    if (string[0] == QChar('+') || string[0] == QChar('-'))
    {
        string.prepend(' ');
    }
    string.prepend('"');
    string.push_back('"');
    return string;
}

/**
 * ��csv��ʽ���ַ��� csvStr���������浽 splitedCsvList
 * splitedCsvList �У� QList<QStringList>��ÿ����Ա��һ�У� QStringList��ÿ����Ա��һ����Ԫ��
 *
 * ��������һ�� 7�����е� csv��ʽ���ַ���
xmlRoot/itemSet/commonGroup/item1/Chinese,"С��<"
xmlRoot/itemSet/commonGroup/item1/English,"����>"
xmlRoot/itemSet/commonGroup/item1/French,"& �ͺ�"
xmlRoot/itemSet/commonGroup/item1/French2,"' ������"
xmlRoot/itemSet/commonGroup/item1/French3,""" ����"
xmlRoot/itemSet/commonGroup/item1/French4,"�س���
    �س���"
xmlRoot/itemSet/commonGroup/item1/French5,"���з�
    ���з�"
 * @param csvStr
 * @param splitedCsvList
 * @return
 */
bool qhParseCSVString(const QString &csvStr, QList<QStringList>& splitedCsvList);


#endif // QHXML_H
