#include "qhXml.h"
#include <set>

#include <assert.h>
#include <QtCore>
#include <QMap>
#include <QRegExp>
#include <QStringList>
#include <QDomDocument>
#include <QDomElement>

#define QSXmlData "QSXmlData"
#define QSXmlArray "QSXmlArray"
#define QSXmlIndex "Index"

#if 1

QDomElement qhDomFindElement(const QDomElement& _e, const QList<QString>& childLst)
{
    QDomElement e = _e;
    QDomElement ce;
    foreach (const QString& s, childLst) {
        ce = e.firstChildElement(s);
        if (ce.isNull())
            return ce;
        else
            e = ce;
    }

    return ce;
}

QList<QDomElement> qhDomFindElements(const QDomElement& _e, QList<QString> childLst)
{
    QDomElement e = _e;
    QList<QDomElement> ceList;

    if (childLst.isEmpty())
        return ceList;

    const QString& child = childLst.first();

    QDomElement ce = e.firstChildElement(child);
    if (ce.isNull())
        return ceList;
    else
    {
        e = ce;
        ceList.push_back(ce);
    }

    do{
        ce = e.nextSiblingElement(child);
        if (!ce.isNull())
        {
            ceList.push_back(ce);
            e = ce;
        }
        else
        {
            break;
        }
    } while(1);

    childLst.removeFirst();
    if (childLst.isEmpty())
    {
        return ceList;
    }

    QList<QDomElement> resultList;
    foreach (const QDomElement& every, ceList) {
         QList<QDomElement> tmpLst = qhDomFindElements(every, childLst);
        if (!tmpLst.isEmpty())
            resultList.append(tmpLst);
    }

    return resultList;
}

QDomElement qhDomFindElement(const QDomElement& _e,
                             const QString& tagName,
                             const QMap<QString, QString>& attributes)
{
    for( QDomElement child = _e.firstChildElement(tagName);
         !child.isNull();
         child = child.nextSiblingElement(tagName))
    {
        bool bBreak = false;
        foreach (const QString& attr, attributes.keys()) {
            if( child.attribute(attr) != attributes.value(attr))
            {
                bBreak = true;
                break;
            }
        }

        if (!bBreak)
        {
            return child;
        }
    }

    return QDomElement();
}

QDomText qhDomFindText(const QDomElement& _e, const QString& text)
{
    QDomNodeList children = _e.childNodes();
    for (int i=0; i<children.size(); i++) {
        QDomText t = children.at(i).toText();
        if (!t.isNull() && t.data() == text)
        {
            return t;
        }
    }

    return QDomText();
}

void parseXmlElement(QDomElement& element, const QString& prefix, QSettings::SettingsMap& settingsMap)
{
    QString _prefix;
    QString eleName = element.tagName();
    if (eleName == QSXmlArray)  //如果是队列成员
    {
        QString attData = element.attribute(QSXmlIndex);

            if (!attData.isNull())
            {
                bool ret;
                int index = attData.toInt(&ret);
                if (ret)
                {
                    //QString sIndex = QString("%1").arg(index, 4, 10, QChar('0'));
                    QString sIndex = QString("%1").arg(index);
                    _prefix = prefix + sIndex;
                }
                else
                {
                    qWarning() << "QSetting file for xml format error: QSXmlArray QSXmlIndex can not covern to int";
                    return;
                }
            }
            else
            {
                qWarning() << "QSetting file for xml format error: QSXmlArray have not QSXmlIndex";
                return;
            }
    }
    else
    {
        _prefix = prefix + element.tagName();
    }

//    QString value = element.text();
//    if (!value.isEmpty())
//        settingsMap.insertMulti(_prefix, value);
    QDomText t = element.firstChild().toText();
    if (!t.isNull())
    {
        //settingsMap.insertMulti(_prefix, t.data());
        settingsMap.insert(_prefix, t.data());
    }
    else
    {
        QString attData = element.attribute(QSXmlData);
        if (!attData.isNull())
            settingsMap.insert(_prefix, attData);
    }

    QDomNodeList children = element.childNodes();
    for (int i=0; i<children.size(); i++) {

        QDomElement e = children.at(i).toElement();
        if (!e.isNull())
            parseXmlElement(e, _prefix+"/", settingsMap);
    }
}

/// Qsetting的读函数，从 文件读到 settingsMap
static bool xmlReadFunc(QIODevice &device, QSettings::SettingsMap &settingsMap)
{
    QDomDocument doc;
    QString errStr;
    int errLine;
    int errCol;
    if (!doc.setContent(&device, &errStr, &errLine, &errCol))
    {
        qWarning() << __FUNCTION__ << ": " << errStr << "at line "
                   << errLine << " column " << errCol;
        return false;
    }

    QDomElement root = doc.documentElement();
    if (!root.isNull())
    {
//        //QString tagName = root.tagName();
//        QDomText t = root.firstChild().toText();
//        if (!t.isNull())
//        {
//            settingsMap.insert(root.tagName(), t.data());
//        }
//        else
//        {
//            QString attData = root.attribute(QSXmlData);
////            QDomNamedNodeMap nodeMap = root.attributes();
////            int n = nodeMap.count();
//            if (!attData.isEmpty())
//                settingsMap.insert(root.tagName(), attData);
//        }
        parseXmlElement(root, QString(), settingsMap);
    }


    return true;
}

bool xmlWriteFunc(QDomDocument& doc, QIODevice &device, const QSettings::SettingsMap &map)
{
    QTextStream ts(&device);
   #if 0
    QByteArray ba = device.readAll();
   #endif
    //QDomElement root;

    QSettings::SettingsMap::ConstIterator it = map.begin();
//    if (it!=map.end())
//    {
//        root = doc.createElement(it.key());
//        root.appendChild(doc.createTextNode(it.value().toString()));
//        doc.appendChild(root);
//    }

    for(/*++it*/; it!=map.end(); ++it)
    {
        QDomNode child = doc;
        QString key = it.key();

        QList<QString> list = key.split("/");
        //Q_ASSERT(root.tagName() == list.at(0));

        // 创建节点
        for (int i=0; i<list.size(); ++i) {
            QString eleName;
            bool ret;
            int index = list[i].toInt(&ret);

            // 是数字，也就是队列的成员
            if (ret)
            {
                QString sIndex = QString("%1").arg(index, QSettingsIntLength, 10, QChar('0'));
                QMap<QString, QString> attrs;
                attrs.insert(QSXmlIndex, sIndex);
                QDomElement tmpChild = qhDomFindElement(child.toElement(), QSXmlArray, attrs);
                        //child.firstChildElement(QSXmlArray);
                if (tmpChild.isNull())
                {
                    tmpChild = doc.createElement(QSXmlArray);
                    tmpChild.setAttribute(QSXmlIndex, sIndex);
                    child.appendChild(tmpChild);
                }

                child = tmpChild;
            }
            else
            {
                QDomElement tmpChild = child.firstChildElement(list.at(i));
                if (tmpChild.isNull())
                {
                    tmpChild = doc.createElement(list.at(i));
                    child.appendChild(tmpChild);
                }
                child = tmpChild;
            }

        }

//        QString xml = doc.toString();
//        qDebug() << xml;
        //child.appendChild( doc.createTextNode(it.value().toString()) );
        child.toElement().setAttribute(QSXmlData, it.value().toString());
    }

    doc.save(ts, 2);
    return true;
}

bool xmlWriteFuncGBK(QIODevice &device, const QSettings::SettingsMap &map)
{
    QDomDocument doc("");
    QDomProcessingInstruction insNode =
            doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"GBK\"");
    doc.appendChild(insNode);
    return xmlWriteFunc(doc, device, map);
}

bool xmlWriteFuncUTF8(QIODevice &device, const QSettings::SettingsMap &map)
{
    QDomDocument doc("");
    QDomProcessingInstruction insNode =
            doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
    doc.appendChild(insNode);
    return xmlWriteFunc(doc, device, map);
}

bool xmlWriteFuncUTF16(QIODevice &device, const QSettings::SettingsMap &map)
{
    QDomDocument doc("");
    QDomProcessingInstruction insNode =
            doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-16\"");
    doc.appendChild(insNode);
    return xmlWriteFunc(doc, device, map);
}

QSettings::Format qhGetQSettingsXmlFormat( EQHEncode encode)
{
    struct TmpEncodeExtension
    {
        QString extension;
        EQHEncode encode;

        bool operator<(const TmpEncodeExtension& other) const
        {
            if (extension < other.extension)
                return true;
            else if (extension > other.extension)
                return false;
            else if ( encode < other.encode )
                return true;
            else if ( encode > other.encode )
                return false;
            else
                return false;
        }

//        bool operator==(const TmpEncodeExtension& other) const
//        {
//            if (extension == other.extension && encode == other.encode)
//                return true;
//            else
//                return false;
//        }
    };

    QString extension("xml");

    static QMap<TmpEncodeExtension, QSettings::Format> s_extMap;
    TmpEncodeExtension tmpEncodeExtension = {extension, encode};
    QMap<TmpEncodeExtension, QSettings::Format>::Iterator it = s_extMap.find(tmpEncodeExtension);
    if (it != s_extMap.end())
        return it.value();

    QSettings::Format xmlFormat = QSettings::InvalidFormat;
    if (encode == EQHEncodeGBK)
    {
        xmlFormat = QSettings::registerFormat(extension, xmlReadFunc, xmlWriteFuncGBK);
    }
    else if (encode == EQHEncodeUTF8)
    {
        xmlFormat = QSettings::registerFormat(extension, xmlReadFunc, xmlWriteFuncUTF8);
    }
    else if (encode == EQHEncodeUTF16)
    {
        xmlFormat = QSettings::registerFormat(extension, xmlReadFunc, xmlWriteFuncUTF16);
    }
    else
    {
        assert(0);
    }
    s_extMap.insert(tmpEncodeExtension, xmlFormat);

    if (xmlFormat == QSettings::InvalidFormat)
    {
        throw "InvalidFormat";
    }

    return xmlFormat;
}

#endif

static bool isQSettingsXmlFormatElement(const QString& prefix,
                                        const QDomElement& element,
                                        QString &errInfo)
{
    QDomNodeList children = element.childNodes();
    std::set<QString> s;
    bool ret = true;
    bool childRet = true;

    for (int i=0; i<children.size(); i++) {
        QDomElement e = children.at(i).toElement();
        if (!e.isNull())
        {
            if (s.find(e.tagName()) != s.end())
            {
                ret = false;
                errInfo += ("have multiple " + prefix + "/" + e.tagName() + "\n");
            }
            else
            {
                s.insert(e.tagName());
            }
            childRet = (isQSettingsXmlFormatElement(prefix + "/" + e.tagName(), e, errInfo) && childRet);
        }
    }

    return (ret && childRet);
}

bool qhIsQSettingsXmlFormatFile(const QString &file, QString &errInfo)
{
    QDomDocument doc;
    QString errStr;
    int errLine;
    int errCol;
    QFile f(file);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        errInfo = "can not open file";
        return false;
    }

    if (!doc.setContent(&f, &errStr, &errLine, &errCol))
    {
        errInfo = "QDomDocument::setContent err: %1 at line %2 column %3";
        errInfo = errInfo.arg(errStr).arg(errLine).arg(errCol);
        return false;
    }

    QDomElement root = doc.documentElement();
    if (root.isNull())
    {
        errInfo = "not find root";
        return false;
    }

    return isQSettingsXmlFormatElement(QString(), root, errInfo);
}

#if 0
bool qhParseCSVString(const QString &csvStr, QList<QStringList>& splitedCsvList)
{
    splitedCsvList.push_back(QStringList());
    QStringList* pList = &splitedCsvList.back();
    //int csvLine = 0;
    int length = csvStr.length();

    struct SPos
    {
        int line;
        int pos;
    };
    QList<SPos> removePos; //等着移除的字符位子

    enum
    {
        EWaitCellBegin,   //等待开始一个单元格
        EWaitCellEndWithComma,    //等待用逗号或换行结束一个单元格
        EWaitCellEndWithQuotation,   //等待用引号结束一个单元格
        EWaitCellWithComma  //等待逗号， 一个引号结束了单元格自后的状态
    } waitCell = EWaitCellBegin;
    int pos = 0;
    int i;

    for(i=0; i<length; ++i)
    {
        if (waitCell == EWaitCellBegin) //等待单元格开始
        {
            if (csvStr[i] == ',')
            {
                pList->push_back(QString());
                waitCell = EWaitCellBegin;
            }
            // 若连续开始三个引号呢，如 xmlRoot/itemSet/commonGroup/item1/French3,""" 引号"
//            else if (csvStr[i] == '"' && i+2<=length && csvStr[i+1] == '"')
//            {
//                i++;
//                pList->push_back(QString());
//                pos = i+1;
//                waitCell = EWaitCellWithComma;
//            }
            else if (csvStr[i] == '"')
            {
                pos = i+1;
                waitCell = EWaitCellEndWithQuotation;   //等待另外一个引号结束单元格
            }
            else if (csvStr[i] == '\n') // 一个新行
            {
                pList->push_back(QString());

                splitedCsvList.push_back(QStringList());
                QStringList* pList = &splitedCsvList.back();

                waitCell = EWaitCellBegin;

                if (i == length-1)
                    break;
            }
            else if(csvStr[i] == ' ' || csvStr[i] == '\t' || csvStr[i] == '\r')
            {
                waitCell = EWaitCellBegin;
            }
            else
            {
                pos = i;
                waitCell = EWaitCellEndWithComma;
            }
        }

        //等待用逗号或换行结束一个单元格
        else if (EWaitCellEndWithComma == waitCell)
        {
            if (csvStr[i] == ',')
            {
                pList->push_back(csvStr.mid(pos, i-pos));
                waitCell = EWaitCellBegin;
            }
            else if (csvStr[i] == '"' && i+2<=length && csvStr[i+1] == '"')
            {
                i++;
                waitCell = EWaitCellEndWithComma;
            }
            else if (csvStr[i] == '"')
            {
                waitCell = EWaitCellEndWithComma;
            }
            else if (csvStr[i] == '\n') // 一个新行
            {
                pList->push_back(csvStr.mid(pos, i-pos));
                waitCell = EWaitCellBegin;

                splitedCsvList.push_back(QStringList());
                QStringList* pList = &splitedCsvList.back();

                if (i == length-1)
                    break;
            }
            else if(csvStr[i] == ' ' || csvStr[i] == '\t' || csvStr[i] == '\r')
            {
                waitCell = EWaitCellEndWithComma;
            }
            else
            {
                waitCell = EWaitCellEndWithComma;
            }
        }

        else if (EWaitCellEndWithQuotation == waitCell)   //等待用引号结束一个单元格
        {
//            if (csvStr[i] == ',')
//            {
//                pList->push_back(csvStr.mid(pos, i-pos));
//                waitCell = EWaitCellBegin;
//            }
//            else
            if (csvStr[i] == '"' && i+2<=length && csvStr[i+1] == '"')
            {
                i++;
                waitCell = EWaitCellEndWithQuotation;
//                SPos p = {splitedCsvList.size()-1, i-pos}; //tian_tag
//                removePos.push_back(p);
            }
            else if (csvStr[i] == '"')
            {
                pList->push_back(csvStr.mid(pos, i-pos));
                pos = i+1;
                waitCell = EWaitCellWithComma;
            }
            else if (csvStr[i] == '\n') // 一个新行
            {
                waitCell = EWaitCellEndWithQuotation;
            }
            else if(csvStr[i] == ' ' || csvStr[i] == '\t' || csvStr[i] == '\r')
            {
                waitCell = EWaitCellEndWithQuotation;
            }
            else
            {
                waitCell = EWaitCellEndWithQuotation;
            }
        }

        else if (EWaitCellWithComma == waitCell)   //等待逗号， 一个引号结束了单元格自后的状态
        {
            if (csvStr[i] == ',')
            {
                //pList->back() += csvStr.mid(pos, i-pos);
                waitCell = EWaitCellBegin;
            }
//            else if (csvStr[i] == '"' && i+2<=length && csvStr[i+1] == '"')
//            {
//                i++;
//                waitCell = EWaitCellEndWithComma;
////                SPos p = {splitedCsvList.size()-1, i-pos}; //tian_tag
////                removePos.push_back(p);
//            }
            else if (csvStr[i] == '"')  //tian_wait 其实是不允许满足的这个判断的
            {
                waitCell = EWaitCellWithComma;
            }
            else if (csvStr[i] == '\n') // 一个新行
            {
                splitedCsvList.push_back(QStringList());
                QStringList* pList = &splitedCsvList.back();

                waitCell = EWaitCellBegin;
            }
            else if(csvStr[i] == ' ' || csvStr[i] == '\t' || csvStr[i] == '\r')
            {
                waitCell = EWaitCellWithComma;
            }
            else
            {
                waitCell = EWaitCellWithComma;
            }
        }

        else
        {
            assert(0);
        }

    }

    if (i == length)
        pList->push_back(csvStr.mid(i-pos));

    return true;
}
#else
bool qhParseCSVString(const QString &csvStr, QList<QStringList>& splitedCsvList)
{
    splitedCsvList.push_back(QStringList());
    QStringList* pList = &splitedCsvList.back();
    //int csvLine = 0;
    int length = csvStr.length();
    bool inQuotation = false;   // 在引号之间
    int pos = 0;
    int i;

    int quotationCount = 0;

    for(i=0; i<length; ++i)
    {
        if (!inQuotation)
        {
            if (csvStr[i] == ',')
            {
                pList->push_back(csvStr.mid(pos, i-pos));
                pos = i+1;
            }
            else if (csvStr[i] == '\n')
            {
                pList->push_back(csvStr.mid(pos, i-pos));
                pos = i+1;
                splitedCsvList.push_back(QStringList());
                pList = &splitedCsvList.back();

                if (i == length-1)
                    break;
            }
            else if (csvStr[i] == '"')
            {
                quotationCount++;
                inQuotation = true;
            }
            else
            {
                //empty
            }
        }
        else    // 在引号里
        {
            if (csvStr[i] == '"')
            {
                quotationCount++;
                inQuotation = false;
            }
            else
            {
                //empty
            }
        }
    }

    // 检查引号个数是否配对
    if (quotationCount % 2 != 0)
        return false;

    if (i == length)
        pList->push_back(csvStr.mid(i-pos));

    for(int j=0; j<splitedCsvList.size(); j++){
        QStringList& list = splitedCsvList[j];
        for(int k =0; k<list.size(); k++)
        {
            QString& s = list[k];
            s = s.trimmed();
            if (s.isEmpty())
                continue;

            if (s.at(0) == '"')
            {
                s.remove(0, 1);
            }
            if (s.at(s.size()-1) == '"')
            {
                s.remove(s.size()-1, 1);
            }
            s.replace("\"\"", "\"");
        }
    }
    return true;
}
#endif
