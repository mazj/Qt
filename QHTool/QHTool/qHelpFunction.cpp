#include <exception>
#include <algorithm>
#include <stdarg.h>
#include <assert.h>
#include <QtCore>
#include <QMap>
#include <QRegExp>
#include <QStringList>
#include <QDomDocument>
#include <QDomElement>

#include "qHelpFunction.h"
//#include "helpFunction.h"

bool qhQStringIs16Bytes(const QString& str, int byteCount)
{
    Q_ASSERT(byteCount>0);
    if ( !(str.startsWith("0x") || str.startsWith("0X")))
        return false;

    if (str.length() != (2+byteCount*2))
        return false;

    for(int i=2; i<str.length(); ++i)
    {
        if (!qhQCharIs16Number(str[i]))
            return false;
    }

    return true;
}

int qhQStringTo16Int(const QString& str, bool *ret)
{
    QString _str = str.trimmed().toLower();
    if (_str.startsWith("0x"))
    {
        _str = _str.right(_str.length()-2);
    }

    return _str.toInt(ret, 16);
}

/*
转义字符    意义                  ASCII码值（十进制）

\a      响铃(BEL)                         007
\b  退格(BS) ，将当前位置移到前一列          008
\f  换页(FF)，将当前位置移到下页开头          012

\n  换行(LF) ，将当前位置移到下一行开头        010
\r  回车(CR) ，将当前位置移到本行开头         013
\t  水平制表(HT) （跳到下一个TAB位置）       009
\v  垂直制表(VT)                            011
\\  代表一个反斜线字符''\'                   092
\'  代表一个单引号（撇号）字符               039
\"  代表一个双引号字符                       034
\0  空字符(NULL)                           000

\ddd    1到3位八进制数所代表的任意字符    三位八进制
\xh...    1到多位十六进制所代表的任意字符    1到多位十六进制

*/
QString &qhConvertCCodeString(QString &cCodeStr)
{
    static QMap<QChar, QChar> charMap;
    if (charMap.isEmpty())
    {
        charMap[QChar('a')] = QChar('\a');
        charMap[QChar('b')] = QChar('\b');
        charMap[QChar('f')] = QChar('\f');
        charMap[QChar('n')] = QChar('\n');
        charMap[QChar('r')] = QChar('\r');
        charMap[QChar('t')] = QChar('\t');
        charMap[QChar('v')] = QChar('\v');
        charMap[QChar('\\')] = QChar('\\');
        charMap[QChar('\'')] = QChar('\'');
        charMap[QChar('"')] = QChar('"');
        //charMap[QChar('0')] = QChar('\0');
    }

    int pos = 0;
    while (pos < cCodeStr.length())
    {
        if (cCodeStr[pos] == '\\')
        {
            if (pos+1 >= cCodeStr.length())
                break;

            if ( charMap.contains(cCodeStr[pos+1]) )
            {
                cCodeStr.replace(pos, 2, charMap.value(cCodeStr[pos+1]));
                ++pos;
            }
            else
            {
                int end;
                bool ret;
                // 一位到三位8 进制
                if (cCodeStr[pos+1].isNumber())
                {
                    QString subStr = cCodeStr.mid(pos+1, 3);
                    int num = qhQString2Int(subStr, 0, 8, &end, &ret);
                    Q_ASSERT(ret);
                    cCodeStr.replace(pos, end+1, QChar(num));
                    ++pos;
                }
                // 一位到8位16 进制
                else if (cCodeStr[pos+1].toLower() == 'x')
                {
                    QString subStr = cCodeStr.mid(pos+2, 8);
                    int num = qhQString2Int(subStr, 0, 16, &end, &ret);
                    Q_ASSERT(ret);
                    cCodeStr.replace(pos, end+2, QChar(num));
                    ++pos;
                }
                else
                {
                    ++pos;
                }
            }
        }
        else
        {
             ++pos;
        }
    }

    return cCodeStr;
}

int qhQCharToNumber(const QChar& c, int base)
{
    if (base == 8)
    {
        if ( (c>='0'&&c<='7') )
        {
            return c.unicode()-'0';
        }
        else
        {
            return -1;
        }
    }
    else if (base == 10 )
    {
        if ( (c>='0'&&c<='9') )
        {
            return c.unicode()-'0';
        }
        else
        {
            return -1;
        }
    }
    else if (base == 16 )
    {
        if ( (c>='0'&&c<='9') )
        {
            return c.unicode()-'0';
        }
        else if ((c>='a'&&c<='f'))
        {
            return c.unicode()-'a'+10;
        }
        else if ((c>='A'&&c<='F'))
        {
            return c.unicode()-'A'+10;
        }
        else
        {
            return -1;
        }
    }
    else
    {
        return -1;
    }
}

int qhQString2Int(const QString& str, int from, int base,
                 int* end, bool *successful)
{
    try{
    Q_ASSERT(from>=0);
    if ( !(from>=0 && from<str.length()) )
    {
        //qDebug() << ;
        throw "位置超出范围";
    }

    int pos = from;

    // 跳过空白
    while(pos <str.length() && str[pos].isSpace())
        ++pos;

    if ( !(from<str.length()) )
    {
        //qDebug() << ;
        throw "全是空白";
    }

    if (base == 8 || base == 10 || base == 16)
    {
        // 可以认为 16 进制兼容 10 进制
        if (base == 16)
        {
            while( pos<str.length() && qhQCharIs16Number(str[pos]) )
            {
                ++pos;
            }
        }
        else if (base == 10)
        {
            while( pos<str.length() && str[pos].isNumber() )
            {
                ++pos;
            }
        }
        else if (base == 8)
        {
            while( pos<str.length() && qhQCharIs8Number(str[pos]) )
            {
                ++pos;
            }
        }
        else
        {
            //empty
        }
        QString subStr = str.mid(from, pos-from);
        bool ret;
        int num = subStr.toInt(&ret, base);
        if (ret)
        {
            if (successful)
                *successful = true;
            if (end)
                *end = pos;
            return num;
        }
        else
        {
            throw "";
        }
    }
    else
    {
        throw "几进制不对";
    }

    } catch (...)
    {
        if (successful)
            *successful = false;
        return -1;
    }
}

int qhQStringFindLineEndPos(const QString & str, int from)
{
    int ir = str.indexOf('\r', from);
    int in = str.indexOf('\n', from);

    if (in != -1 && ir == -1)
    {
        return in;
    }
    else if (in == -1 && ir != -1)
    {
        return ir;
    }
    else if (in != -1 && ir != -1)
    {
        int maxV = std::max(in, ir);
        int minV = std::min(in, ir);

        if (minV+1 == maxV)
        {
            return maxV;
        }
        else
        {
            return minV;
        }
    }
    else
    {
        return -1;
    }
}

//void qhRemoveExegesisInCode_(QString & code)
//{
//    //去除块注释 /*   */ 和 去除行注释必须同时处理，两者是 同级的

//    int pos = 0;
//    int index = 0;

//    while ( ( index=code.indexOf( QChar('/'), pos ) ) != -1 )
//    {
//        // 航注释
//        if (code[index+1] == '/')
//        {
//            int endPos = qhQStringFindLineEndPos(code, index+1);
//            if (endPos == -1)   //没有行尾则到字符串尾端
//                endPos = code.size()-1;
//            code.remove(index, endPos-index+1);
//            pos = 0;
//        }
//        //块注释
//        else if (code[index+1] == '*')
//        {
//            int endPos = code.indexOf("*/", index+1);
//            if (endPos == -1) //没有行尾则到字符串尾端
//            {
//                throw std::runtime_error("代码格式错误");
//            }
//            code.remove(index, endPos-index+2);
//            pos = 0;
//        }
//        // 处理把 / 当成字符的情况 '/'， 暂时不支持 字符串中带 / 的情况
//        else if (code[index+1] == '\'' && code[index-1] == '\'')
//        {
//            pos = index+1;
//        }
//        else  //这里 只有  / 没有 //和 /* 的情况 抛出异常
//        {
//            throw std::runtime_error("代码格式错误");
//        }
//    }


////     //去除块注释 /*   */
////    QString regStr("/\\*.*\\*/"); //  写成 /\\**\\*/   不行

//}

void qhRemoveExegesisInCode_(QString & code)
{
    //去除块注释 /*   */ 和 去除行注释必须同时处理，两者是 同级的

    //int pos = 0;
    int index = 0;
    bool bInYH = false; //在双引号里面

    while ( index < code.length() )
    {
        // 没有在引号里
        if (!bInYH)
        {
            if (code[index] == '/')
            {
                // 行注释
                if (code[index+1] == '/')
                {
                    int endPos = qhQStringFindLineEndPos(code, index+2);
                    if (endPos == -1)   //没有行尾则到字符串尾端
                        endPos = code.size()-1;
                    code.remove(index, endPos-index);
                    // index 不变
                }
                //块注释,保持源代码的行数不变
                else if (code[index+1] == '*')
                {
                    int endPos = code.indexOf("*/", index+2);
                    if (endPos == -1) //没有行尾则到字符串尾端
                    {
                        throw std::runtime_error("代码格式错误");
                    }
                    int lineCount = code.mid(index, endPos-index+2).count('\n');
                    QString linesStr(lineCount, '\n');
                    code.replace(index, endPos-index+2, linesStr);
                    index += lineCount;
                }
                // 处理把 / 当成字符的情况 '/'， 暂时不支持 字符串中带 / 的情况
                else if (code[index+1] == '\'' && index-1>=0 && code[index-1] == '\'')
                {
                    index += 2;
                }
                else  //这里 只有  / 没有 //和 /* 的情况 抛出异常
                {
                    index += 2;
                    //qDebug() << "code[index+1]=" << code[index+1];
                    //throw std::runtime_error("代码格式错误");
                }
            }
            else if (code[index] == '"')
            {
                bInYH = true;
                ++index;
            }
            else
            {
                ++index;
            }
        }

        // 在引号里
        else
        {
            if (code[index] == '"')
            {
                bInYH = false;
                ++index;
            }
            // 处理字符串中有引号的情况
            else if (code[index] == '\\' && code[index+1] == '"')
            {
                index += 2;
            }
            else
            {
                ++index;
            }
        }
    }


//     //去除块注释 /*   */
//    QString regStr("/\\*.*\\*/"); //  写成 /\\**\\*/   不行

}

QString& qhReadQFileString(const QString& filePath, QString& content)
{
    QFile file(filePath);
    bool ret = file.open(QIODevice::Text|QIODevice::ReadOnly);
    if (!ret)
        return content;

    QTextStream s(&file);
    content = s.readAll();
    return content;
}

bool qhWriteQFileString(const QString& filePath, const QString &content,
                        QTextCodec * codec)
{
    QFile file(filePath);
    bool ret = file.open(QIODevice::Text|QIODevice::WriteOnly|QIODevice::Truncate);
    if (!ret)
        return false;

    QTextStream s(&file);
    if (codec)
        s.setCodec(codec);

    s << content;
    return true;
}

int qhStartTimerAtTime(QObject* pObj, const QTime& runTime)
{
     Q_ASSERT(pObj);
    QTime now = QTime::currentTime();
    if (runTime < now)
    {
        return 0;
    }
    else
    {
        int ms = now.msecsTo(runTime);
        return pObj->startTimer(ms);
    }
}


/**
 * 解析 字符串形如 nameStr = 54 的形式
 * @param code
 * @param name
 * @param value
 */
static void analysis1(QString code, QString &name, QString & value)
{
    code.remove(QChar(','));
    code.remove(QRegExp("\\s*"));

    int index = code.indexOf("=");
    if (index == -1)
    {
        assert(0);
    }

    name = code.left(index);
    value = code.right(code.size() - index - 1);
}

#if 0
QMap<int, QString> qhGetEnumMap(const QString &code, QMap<int, QString> &map)
{
    //函数内 没有检测 map 的合法性，没有 检查 value值是否有重复的
    QString _code = code;
    qhRemoveExegesisInCode_(_code);

    QMap<QString, int> mapOppo;
    QStringList valueList = map.values();
//    int pos = 0;
    int value= 0;
    QString valueStr;
    QString name;

    bool fail = false;
    QString failNames;
    QString errStr;

    _code.remove(QRegExp("enum.*\\{")); //
    _code.remove(QRegExp("\\}.*"));

    QRegExp rx(".+=.+");
    QStringList list = _code.split(QChar(','), QString::SkipEmptyParts);
    foreach(const QString &c, list)
    {
        if (rx.exactMatch(c))
        {
            bool ret = false;
            analysis1(c, name, valueStr);
            int iTmp = valueStr.toInt(&ret, 10);
            if (ret)
            {
                value = iTmp;
                map.insertMulti(value, name);

                if (!mapOppo.contains(name))
                    mapOppo.insert(name, value);
            }
            else
            {
                if (mapOppo.contains(valueStr)) //处理下一个枚举值引用上一个枚举值的情况
                {
                    value = mapOppo.value(valueStr);
                    map.insertMulti(value, name);
                }
                else
                {
                    //查找 map 是是否已经有了 该 enum 项
                    bool found = false;
                    foreach (const QString &str, valueList)
                    {
                        if (str==name)
                        {
                            found = true;
                            break;
                        }
                        //处理 namespace::name 与 name 的情况
                        else
                        {
                            const QString *shortS = NULL;
                            const QString *longS = NULL;

                            if (str.length() < name.length())
                            {
                                shortS = &str;
                                longS = &name;
                            }
                            else if (str.length() > name.length())
                            {
                                shortS = &name;
                                longS = &str;
                            }
                            else
                            {
                                continue;
                            }
                            int tmpSize = (*shortS).size();
                            if ( (*shortS)==(*longS).right(tmpSize)
                                 && (*longS).mid((*longS).length()-tmpSize-2, 2)=="::" )
                            {
                                found = true;
                                break;
                            }
                        }
                    }
                    if ( ! found )
                    {
                        failNames.append(name+", ");
                        fail = true;
                    }

                }
            }
        }
        else
        {
            QString c1(c);
            c1.remove(QRegExp("\\s*"));
            if (c1.isEmpty())   //为了兼容最后多出来一个逗号的情况
                continue;
            map.insertMulti(value, c1);

            if (!mapOppo.contains(c1))
                mapOppo.insert(c1, value);
        }
        value++;
    }

    //解析错误检查
    foreach (const QString &s, map.values()) {
        if (s.at(0).isDigit())
        {
            fail = true;
            errStr += s+QString(" begin with digit; ");
        }
        int size = s.size();
        for(int i=0; i<size; i++)
        {
            if ( !(s[i].isLetter() || s[i].isDigit() || s[i]=='_'
                   || (s[i]==':'&&s[++i]==':')) )
            {
                fail = true;
                errStr += (s+QString(" format error! \n"));
            }
        }

    }

    if (fail)
    {
        //没找到映射值的 枚举值
        Q_ASSERT_X(failNames.isEmpty(), "analy enum item fail", QString("none found's enum values : %1, "
                                                 "try add QH_GET_ENUM_ITEM(M_I(enumItem)) for every one")
                   .arg(failNames).toStdString().data());
//        errStr += (QString("none found's enum values : \n"));
//        errStr += failNames;
        Q_ASSERT_X(errStr.isEmpty(), "analy enum item err", errStr.toStdString().data());
//        qDebug() << errStr;

    }

    return map;
}

#else

bool mapContains(const QMap<QString, int> & map, const QString &key, int &value)
{
    if (map.contains(key))
    {
        value = map.value(key);
        return true;
    }
    else
    {
        foreach (const QString &str, map.uniqueKeys()) {
            const QString *shortS = NULL;
            const QString *longS = NULL;
            if (str.length() < key.length())
            {
                shortS = &str;
                longS = &key;
            }
            else if (str.length() > key.length())
            {
                shortS = &key;
                longS = &str;
            }
            else
            {
                continue;
            }

            int tmpSize = (*shortS).size();
            if ( (*shortS)==(*longS).right(tmpSize)
                 && (*longS).mid((*longS).length()-tmpSize-2, 2)=="::" )
            {
                value = map.value(str);
                return true;
            }
        }

        return false;
    }
}

QMap<int, QString> qhGetEnumMap(const QString &code, QMap<int, QString> &map)
{
    QString _code = code;
    qhRemoveExegesisInCode_(_code);

    // 把 map 的key 和 value 倒过来放到 mapOppo
    QMap<QString, int> mapOppo;
    foreach(int key, map.uniqueKeys())
    {
        foreach(const QString &str, map.values(key))
        {
            if (!mapOppo.contains(str))
                mapOppo.insert(str, key);
            else
            {
                qDebug() << "map contain mutul value: " << str;
                Q_ASSERT(0);
            }
        }
    }

    int value= 0;
    QString valueStr;
    QString name;

    bool fail = false;
//    QString failNames;
    QString errStr;

    _code.remove(QRegExp("enum.*\\{")); //
    _code.remove(QRegExp("\\}.*"));

    QRegExp rx(".+=.+");
    QStringList list = _code.split(QChar(','), QString::SkipEmptyParts);
    foreach(const QString &c, list)
    {
        if (rx.exactMatch(c))
        {
            bool ret = false;
            analysis1(c, name, valueStr);
            int iTmp = valueStr.toInt(&ret, 10);
            if (ret)
            {
                int v;
                if (!mapContains(mapOppo, name, v))
                {
                    value = iTmp;
                    map.insertMulti(value, name);
                    mapOppo.insert(name, value);
                }
                else
                {
                    value = v;
                }
            }
            else
            {
                int v;
                if (!mapContains(mapOppo, name, v))
                {
                    if (mapContains(mapOppo, valueStr, v)) //处理下一个枚举值引用上一个枚举值的情况
                    {
                        value = v;
                        map.insertMulti(value, name);
                        mapOppo.insert(name, value);
                    }
                    else
                    {
                        qDebug() << "can not analysis1 " << c;
                        Q_ASSERT(0);
                    }
                }
                else
                {
                    value = v;
                }
            }
        }
        else
        {
            QString c1(c);
            c1.remove(QRegExp("\\s*"));
            if (c1.isEmpty())   //为了兼容最后多出来一个逗号的情况
                continue;

            int v;
            if (!mapContains(mapOppo, c1, v))
            {
                map.insertMulti(value, c1);
                mapOppo.insert(c1, value);
            }
            else
            {
                value = v;
            }
        }
        value++;
    }

    //解析错误检查
    foreach (const QString &s, map.values()) {
        if (s.at(0).isDigit())
        {
            fail = true;
            errStr += s+QString(" begin with digit; ");
        }
        int size = s.size();
        for(int i=0; i<size; i++)
        {
            if ( !(s[i].isLetter() || s[i].isDigit() || s[i]=='_'
                   || (s[i]==':'&&s[++i]==':')) )
            {
                fail = true;
                errStr += (s+QString(" format error! \n"));
            }
        }

    }

    if (fail)
    {
        //没找到映射值的 枚举值
//        Q_ASSERT_X(failNames.isEmpty(), "analy enum item fail", QString("none found's enum values : %1, "
//                                                 "try add QH_GET_ENUM_ITEM(M_I(enumItem)) for every one")
//                   .arg(failNames).toStdString().data());
//        errStr += (QString("none found's enum values : \n"));
//        errStr += failNames;
        Q_ASSERT_X(errStr.isEmpty(), "analy enum item err", errStr.toStdString().data());
//        qDebug() << errStr;

    }

    return map;
}

#endif

QMap<int, QString> qhGetEnumMap(int count, ...)
{
    int _count = count;
    QMap<int, QString> map;
    va_list args;

    va_start(args, count);
    for(int i=0; i<_count; i++)
    {
        int key = va_arg(args, int);
        const char * name = va_arg(args, const char *);
        if (strcmp(name, "0") == 0)
            break;

        map.insertMulti(key, QString(name).remove(QRegExp("\\s*")));
    }
    va_end(args);

    return map;
}






