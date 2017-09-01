#include "XmlSettings.h"

#include <QDebug>
#include <QStringList>
#include <QDomElement>
#include <boost/bind.hpp>


void parseXmlElement(QDomElement& element, const QString& prefix, QSettings::SettingsMap& settingsMap)
{
    QString _prefix = prefix + element.tagName();
//    QString value = element.text();
//    if (!value.isEmpty())
//        settingsMap.insertMulti(_prefix, value);

    QDomNodeList children = element.childNodes();
    for (int i=0; i<children.size(); i++) {
        QDomText t = children.at(i).toText();
        if (!t.isNull())
        {
            //settingsMap.insertMulti(_prefix, t.data());
            settingsMap.insert(_prefix, t.data());
            continue;
        }
        QDomElement e = children.at(i).toElement();
        if (!e.isNull())
            parseXmlElement(e, _prefix+"/", settingsMap);
    }
}

bool XmlSettings::xmlReadFunc(QIODevice &device, QSettings::SettingsMap &settingsMap)
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
        parseXmlElement(root, QString(), settingsMap);
    }
//    QString value = root.text();
//    if (!value.isEmpty())
//        settingsMap.insertMulti(root.tagName(), value);

//    QDomNodeList children = root.childNodes();
//    for (const QDomNode &n, children) {
//        QDomElement e = n.toElement();
//        if (!e.isNull())
//            parseXmlElement(e, root.tagName(), settingsMap);
//    }

    return true;
}

bool XmlSettings::xmlWriteFunc(QIODevice &device, const QSettings::SettingsMap &map)
{
    QTextStream ts(&device);
   #if 1
    QByteArray ba = device.readAll();
   #endif
    QDomDocument doc;
    QDomElement root;

    QSettings::SettingsMap::ConstIterator it = map.begin();
    if (it!=map.end())
    {
        root = doc.createElement(it.key());
        root.appendChild(doc.createTextNode(it.value().toString()));
        doc.appendChild(root);
    }

    for(++it; it!=map.end(); ++it)
    {
        QDomElement child = root;
        QString key = it.key();

        QList<QString> list = key.split("/");
        Q_ASSERT(root.tagName() == list.at(0));
        for (int i=1; i<list.size(); ++i) {
            QDomElement tmpChild = child.firstChildElement(list.at(i));
            if (tmpChild.isNull())
            {
                tmpChild = doc.createElement(list.at(i));
                child.appendChild(tmpChild);
            }

            child = tmpChild;
        }

        child.appendChild( doc.createTextNode(it.value().toString()) );
    }

    doc.save(ts, 2);
    return true;
}

QSettings::Format XmlSettings::getQSettingsXmlFormat(const QString & extension)
{
    static QMap<QString, QSettings::Format> s_extMap;
    QMap<QString, QSettings::Format>::Iterator it = s_extMap.find(extension);
    if (it != s_extMap.end())
        return it.value();

    QSettings::Format xmlFormat = QSettings::InvalidFormat;
//    xmlFormat = QSettings::registerFormat(extension, xmlReadFunc, xmlWriteFunc);
//    s_extMap.insert(extension, xmlFormat);

//    if (xmlFormat == QSettings::InvalidFormat)
//    {
//        throw "InvalidFormat";
//    }

    return xmlFormat;
}

XmlSettings::XmlSettings(const QString & fileName,
                         const QString & extension,
                         QObject * parent) :
    QSettings(fileName, getQSettingsXmlFormat(extension), parent)
{
}
