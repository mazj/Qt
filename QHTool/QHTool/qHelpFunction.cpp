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
ת���ַ�    ����                  ASCII��ֵ��ʮ���ƣ�

\a      ����(BEL)                         007
\b  �˸�(BS) ������ǰλ���Ƶ�ǰһ��          008
\f  ��ҳ(FF)������ǰλ���Ƶ���ҳ��ͷ          012

\n  ����(LF) ������ǰλ���Ƶ���һ�п�ͷ        010
\r  �س�(CR) ������ǰλ���Ƶ����п�ͷ         013
\t  ˮƽ�Ʊ�(HT) ��������һ��TABλ�ã�       009
\v  ��ֱ�Ʊ�(VT)                            011
\\  ����һ����б���ַ�''\'                   092
\'  ����һ�������ţ�Ʋ�ţ��ַ�               039
\"  ����һ��˫�����ַ�                       034
\0  ���ַ�(NULL)                           000

\ddd    1��3λ�˽�����������������ַ�    ��λ�˽���
\xh...    1����λʮ������������������ַ�    1����λʮ������

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
                // һλ����λ8 ����
                if (cCodeStr[pos+1].isNumber())
                {
                    QString subStr = cCodeStr.mid(pos+1, 3);
                    int num = qhQString2Int(subStr, 0, 8, &end, &ret);
                    Q_ASSERT(ret);
                    cCodeStr.replace(pos, end+1, QChar(num));
                    ++pos;
                }
                // һλ��8λ16 ����
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
        throw "λ�ó�����Χ";
    }

    int pos = from;

    // �����հ�
    while(pos <str.length() && str[pos].isSpace())
        ++pos;

    if ( !(from<str.length()) )
    {
        //qDebug() << ;
        throw "ȫ�ǿհ�";
    }

    if (base == 8 || base == 10 || base == 16)
    {
        // ������Ϊ 16 ���Ƽ��� 10 ����
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
        throw "�����Ʋ���";
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
//    //ȥ����ע�� /*   */ �� ȥ����ע�ͱ���ͬʱ���������� ͬ����

//    int pos = 0;
//    int index = 0;

//    while ( ( index=code.indexOf( QChar('/'), pos ) ) != -1 )
//    {
//        // ��ע��
//        if (code[index+1] == '/')
//        {
//            int endPos = qhQStringFindLineEndPos(code, index+1);
//            if (endPos == -1)   //û����β���ַ���β��
//                endPos = code.size()-1;
//            code.remove(index, endPos-index+1);
//            pos = 0;
//        }
//        //��ע��
//        else if (code[index+1] == '*')
//        {
//            int endPos = code.indexOf("*/", index+1);
//            if (endPos == -1) //û����β���ַ���β��
//            {
//                throw std::runtime_error("�����ʽ����");
//            }
//            code.remove(index, endPos-index+2);
//            pos = 0;
//        }
//        // ����� / �����ַ������ '/'�� ��ʱ��֧�� �ַ����д� / �����
//        else if (code[index+1] == '\'' && code[index-1] == '\'')
//        {
//            pos = index+1;
//        }
//        else  //���� ֻ��  / û�� //�� /* ����� �׳��쳣
//        {
//            throw std::runtime_error("�����ʽ����");
//        }
//    }


////     //ȥ����ע�� /*   */
////    QString regStr("/\\*.*\\*/"); //  д�� /\\**\\*/   ����

//}

void qhRemoveExegesisInCode_(QString & code)
{
    //ȥ����ע�� /*   */ �� ȥ����ע�ͱ���ͬʱ���������� ͬ����

    //int pos = 0;
    int index = 0;
    bool bInYH = false; //��˫��������

    while ( index < code.length() )
    {
        // û����������
        if (!bInYH)
        {
            if (code[index] == '/')
            {
                // ��ע��
                if (code[index+1] == '/')
                {
                    int endPos = qhQStringFindLineEndPos(code, index+2);
                    if (endPos == -1)   //û����β���ַ���β��
                        endPos = code.size()-1;
                    code.remove(index, endPos-index);
                    // index ����
                }
                //��ע��,����Դ�������������
                else if (code[index+1] == '*')
                {
                    int endPos = code.indexOf("*/", index+2);
                    if (endPos == -1) //û����β���ַ���β��
                    {
                        throw std::runtime_error("�����ʽ����");
                    }
                    int lineCount = code.mid(index, endPos-index+2).count('\n');
                    QString linesStr(lineCount, '\n');
                    code.replace(index, endPos-index+2, linesStr);
                    index += lineCount;
                }
                // ����� / �����ַ������ '/'�� ��ʱ��֧�� �ַ����д� / �����
                else if (code[index+1] == '\'' && index-1>=0 && code[index-1] == '\'')
                {
                    index += 2;
                }
                else  //���� ֻ��  / û�� //�� /* ����� �׳��쳣
                {
                    index += 2;
                    //qDebug() << "code[index+1]=" << code[index+1];
                    //throw std::runtime_error("�����ʽ����");
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

        // ��������
        else
        {
            if (code[index] == '"')
            {
                bInYH = false;
                ++index;
            }
            // �����ַ����������ŵ����
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


//     //ȥ����ע�� /*   */
//    QString regStr("/\\*.*\\*/"); //  д�� /\\**\\*/   ����

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
 * ���� �ַ������� nameStr = 54 ����ʽ
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
    //������ û�м�� map �ĺϷ��ԣ�û�� ��� valueֵ�Ƿ����ظ���
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
                if (mapOppo.contains(valueStr)) //������һ��ö��ֵ������һ��ö��ֵ�����
                {
                    value = mapOppo.value(valueStr);
                    map.insertMulti(value, name);
                }
                else
                {
                    //���� map ���Ƿ��Ѿ����� �� enum ��
                    bool found = false;
                    foreach (const QString &str, valueList)
                    {
                        if (str==name)
                        {
                            found = true;
                            break;
                        }
                        //���� namespace::name �� name �����
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
            if (c1.isEmpty())   //Ϊ�˼����������һ�����ŵ����
                continue;
            map.insertMulti(value, c1);

            if (!mapOppo.contains(c1))
                mapOppo.insert(c1, value);
        }
        value++;
    }

    //����������
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
        //û�ҵ�ӳ��ֵ�� ö��ֵ
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

    // �� map ��key �� value �������ŵ� mapOppo
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
                    if (mapContains(mapOppo, valueStr, v)) //������һ��ö��ֵ������һ��ö��ֵ�����
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
            if (c1.isEmpty())   //Ϊ�˼����������һ�����ŵ����
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

    //����������
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
        //û�ҵ�ӳ��ֵ�� ö��ֵ
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






