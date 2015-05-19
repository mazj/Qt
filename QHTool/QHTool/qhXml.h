/**
  \file qhXml.h
  \brief 封装 qt中关于 xml的一些操作，qt的帮助函数以qh开头

  \note 为了查找一个特定帮助函数好找， 每个函数定义了 一个 \\test 标签，一般的内容为 Help控件
  \test 为了查找一个特定帮助函数好找， 每个函数定义了 一个 \\test 标签，一般的内容为 Help控件
  \author 田海福
  \date 2014.10.17  创建
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
  找到 节点 e的第一个满足条件的子孙节点，如
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
则 e传入 first节点，childLst的内容是 secong third，则返回 节点 <third>thirdtext1</third>
 * @param e
 * @param childLst
 * @return
 *\test HelpQDomElement
 */
QDomElement qhDomFindElement(const QDomElement& _e, const QList<QString>& childLst);

/**
 * @brief qhDomFindElements
 *  找到 节点 e的满足条件的所有子孙节点，如
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
那么 e传入 first节点，childLst的内容是 secong third，
则返回 节点 <third>thirdtext1</third> <third>thirdtext2</third> <third>thirdtext3</third> <third>thirdtext4</third>

 * @param e
 * @param childLst
 * @return
 *\test HelpQDomElement
 */
QList<QDomElement> qhDomFindElements(const QDomElement& _e, QList<QString> childLst);

/**
 * @brief qhDomFindElement
 *  查找 tagName是 tagName，属性值有 attributes的一级子节点
 * @param _e
 * @param tagName 为空则 不判断tagName
 * @param attributes
 * @return
 */
QDomElement qhDomFindElement(const QDomElement& _e, const QString &tagName,
                             const QMap<QString, QString>& attributes);

/**
 * @brief 找到 QDomElement  _e 的 QDomText 类型的子节点，子节点的内容要是 text
 * @param _e
 * @param text
 * @return
 *\test HelpQDomElement
 */
QDomText qhDomFindText(const QDomElement& _e, const QString& text);

/**
 * @brief getQSettingsXmlFormat
 * QSettings 默认不支持以 xml格式保存配置信息，需要用户主动注册处理 处理xml格式的函数.
 *
 * 这里用 xml 格式保存 QSettings 信息 在 符合xml规范的基础上再有些限制。如下面的例子
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

1.节点名称要满足 xml规范，如节点名称不能是 以数字开头的字符（例〈1〉〈/1〉）.
 在满足 xml规范前提下
    <1>节点名称中不能出现 斜杠和反斜杠（QSettings 限制）
    <2>属性 QSXmlData 认为是 QSetting的key的值
    <3> tagName 是 QSXmlArray的按照 QSetting的队列成员处理，属性 Index的值是队列成员的索引值。
        tagName 为size的节点的值， 在 QSetting中认为是队列的大小。

2.同一级的节点名称不能同名，如
<dido_config_table>
    <a02>0</a02>
    <a02>1</a02>
</dido_config_table>
不可以
3. QSettings 的 key 与 xml的节点路径对应，如 dido_config_table/device/commonDevice/di/board_type_1/_1
对应节点 <_1>255</_1>；
key值对应的value规则：
（1）若 key对应的节点有值，则value为对应的值，如 <_1>255</_1>
（2）若key对应的节点无值，则:
        若 该节点存在属性 QSXmlData，则 属性QSXmlData的值为key的value
4.同一级的节点和key值 没有先后顺序之分， 这与 QSettings 一致
5.只处理节点属性是 QSXmlData Index.
6.空节点认为不是 QSettings 的 key，如 <NULL></NULL>
 * @param encode    保存文件时的编码方式，只在保存xml配置文件时有效
* @return QSettings::Format,若返回值 是 QSettings::IniFormat 则无效
 *  \test HelpQSettings
 */
QSettings::Format qhGetQSettingsXmlFormat(EQHEncode encode = EQHEncodeUTF8);
const int QSettingsIntLength = 4;

/**
 * 判断是不是标准的 QSettingsXmlFormat 格式的文件
 * @param file
 * @return
 */
bool qhIsQSettingsXmlFormatFile(const QString& file, QString& errInfo);

/**
 * @brief 字符串转化成 csv格式的字符串
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
 * @brief 字符串转化成 csv格式的字符串,并兼容 excel 对打开 csv文件时的处理
 *
 * csv  在转化成 xls格式时，若 一个单元格的字符串以 +或-开头，excel则认为是函数（单元格开头的+和-在excel有特殊意义)，
 * 为避免这一点，在 +或-前加个空格即可
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
 * 将csv格式的字符串 csvStr解析，保存到 splitedCsvList
 * splitedCsvList 中， QList<QStringList>的每个成员是一行， QStringList的每个成员是一个单元格
 *
 * 如下面是一个 7行两列的 csv格式的字符串
xmlRoot/itemSet/commonGroup/item1/Chinese,"小于<"
xmlRoot/itemSet/commonGroup/item1/English,"大于>"
xmlRoot/itemSet/commonGroup/item1/French,"& 和号"
xmlRoot/itemSet/commonGroup/item1/French2,"' 单引号"
xmlRoot/itemSet/commonGroup/item1/French3,""" 引号"
xmlRoot/itemSet/commonGroup/item1/French4,"回车符
    回车符"
xmlRoot/itemSet/commonGroup/item1/French5,"换行符
    换行符"
 * @param csvStr
 * @param splitedCsvList
 * @return
 */
bool qhParseCSVString(const QString &csvStr, QList<QStringList>& splitedCsvList);


#endif // QHXML_H
