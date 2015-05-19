/**
  \file qHelpFunction.h
  \brief 封装 qt的 qtCore和qtXml一些操作 到函数中，应用程序可以快捷调用，qt的帮助函数以qh开头

  \note 为了查找一个特定帮助函数好找， 每个函数定义了 一个 \\test 标签，一般的内容为 Help控件
  \test 为了查找一个特定帮助函数好找， 每个函数定义了 一个 \\test 标签，一般的内容为 Help控件
  \author 田海福
  \date 2014.2.24  创建
  */

#ifndef QHELPFUNCTION_H
#define QHELPFUNCTION_H

#include <assert.h>

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
#include "SettingTextCodec.hpp"


class QSettings;
class QDomElement;
class QDomNode;
class QDomText;


/**
  Q_ASSERT 在 非 debug 时什么也不干，
  QH_VERIFY 在 非 debug 时 依然求值，但不判断
  */
#ifdef QT_NO_DEBUG
#define QH_VERIFY(explore) explore
#else
#define QH_VERIFY(explore) Q_ASSERT(explore)
#endif


/**
 * @brief 分析c代码中的 字符串
 * c c++ 中的字符串中 会有转义字符，该函数的功能是 把转义字符的形式 转化成 本来的字符串
 * \note 只能处理单字节的转义字符
 * 如：传入 cCodeStr "17766\noo\rthth\t\\"，则 \n \r \t \\ 都会被替换成实际字符
 * @param cCodeStr
 */
QString& qhConvertCCodeString(QString &cCodeStr);

/**
 * @brief is16Number 判断QChar 是否是 16 进制的数字或字母
 * @param c
 * @return
 * \test HelpQChar
 */
inline bool qhQCharIs16Number(const QChar& c)
{
    if ( (c>='0'&&c<='9')
         || (c>='a'&&c<='f')
         || (c>='A'&&c<='F'))
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * @brief qhQStringIs16Bytes
 *  判断是否是 严格的 16进制 几字节的形式
 *  qhQStringIs16Bytes("0x00d8", 2) 返回真
 *  qhQStringIs16Bytes("0xd8", 2) 返回假
 * @param str
 * @param byteCount 几个字节
 * @return
 * \test HelpQString
 */
bool qhQStringIs16Bytes(const QString& str, int byteCount);

/**
 * @brief qhQStringTo16Int
 *  把字符串转化成16进制的数字，字符串是否以 0x 或 0X开头都可以
 * qhQStringTo16Int("0xd2") 返回 0xd2
 * qhQStringTo16Int("d2") 返回 0xd2
 * qhQStringTo16Int("dR") 转化失败
 * @param str
 * @param ret 转化是否成功
 * @return
 *  * \test HelpQString
 */
int qhQStringTo16Int(const QString& str, bool *ret = NULL);

/**
 * @brief qhQCharIs8Number 判断QChar 是否是 8 进制的数字
 * @param c
 * @return
 */
inline bool qhQCharIs8Number(const QChar& c)
{
    if ( (c>='0'&&c<='7') )
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * @brief qhQCharToNumber 把QChar转化成数字，不处理负号
 * @param c
 * @param base 几进制，目前只有 16 和 10进制 8进制
 * @return 返回转化成功的数，失败返回 -1
 *  * \test HelpQChar
 */
int qhQCharToNumber(const QChar& c, int base = 10);



/**
 * @brief qhString2Int 把 QString 转化成 int
 * 如 qhString2Int(QString("qsw23rf"),1) 会转化失败
 * qhString2Int(QString("qsw23rf"),3) 会转化成功，返回23，end返回5
 * qhString2Int(QString("qsw23rf"),4) 会转化成功，返回4，end返回5
 * qhString2Int(QString("qsw 23rf"),3) 会转化成功，返回23，end返回6
 *
 * @param str
 * @param successful [out] 转化是否成功
 * @param from      开始转化的位置
 * @param end [out] 转化结束位置
 * @param base 多少进制,目前只能传10 或 16 或 8
 * @return  转化成的数字，转化失败返回 -1

 * \test HelpQString
 */
int qhQString2Int(const QString& str, int from=0, int base = 10, int* end=NULL, bool *successful = NULL);

/**
 * 找到 QString str 的 第一行的结尾位置
 * @param str
 * @param from 从第几个字符开始查找
 * @return 结尾位置，没找到返回-1
 *
 *  注：window 的换行 在磁盘存贮的是回车换行俩字符，
 * 但在 以文本格式打开时换行就只有一个换行符
 * \test HelpQString
 */
int qhQStringFindLineEndPos(const QString & str, int from = 0);

/**
 * 重载函数
 * @param [in][out]code
 */
void qhRemoveExegesisInCode_(QString &code);

/**
 * 去掉 c c++代码 code 中 的注释
 * @param code
 * @return 去掉 注释 后的代码
 * \note 去掉注释后的字符串 跟之前的行数一致.
 *       只能处理格式正确的 c c++代码，格式不正确的可能会出错.
 *       没法处理宏
 */
inline QString qhRemoveExegesisInCode(const QString &code)
{
    QString c = code;
    qhRemoveExegesisInCode_(c);
    return c;
}

/**
 * @brief qhQFileString
 *
 * 快捷函数 得到文件 filePath 的所有内容
 * @param filePath 文件路径
 * @param content  用来存放文件内容
 * @return 返回文件内容
 * \test HelpQFile
 */
QString& qhReadQFileString(const QString& filePath, QString& content);

/**
 * @brief qhWriteQFileString 把 content 内容写到 文件filePath中，
 * 若 filePath没有则创建。若filePath已经有，则清空原有内容
 * @param filePath
 * @param content
 * @return
 * \test HelpQFile
 */
bool qhWriteQFileString(const QString& filePath, const QString &content,
                        QTextCodec *codec = NULL);

/**
	判断QList 中是否有重复元素。
	若有则返回真， repeat 存放 第一批重复元素的位置
	没有返回假
	\test HelpQList
*/
template<typename T>
bool qhQListContainRepeatEle(const QList<T>& list, QSet<int>* repeat = NULL)
{
	bool ret = false;
	for(int i=0; i<list.size(); ++i)
	{
		const T& v = list[i];
		for(int j=i+1; j<list.size(); ++j)
		{
			if (v == list[j])
			{
                if (repeat)
                {
                    repeat->insert(i);
                    repeat->insert(j);
                    ret = true;
                }
                else
                {
                    ret = true;
                    break;
                }
			}
		}

		if (ret)
		{
			break;
		}
	}

    return ret;
}

/**
 * @brief 去除 QList 中的重复元素
 *
 * 去除 QList 中的重复元素，非重复元素的顺序不变.重复元素去除后部的元素。例如
 * 传入 list是 “2” “1” “3” “1” “0”，则传出是 “2” “1” “3” “0”
 * \test HelpQList
 */
template<typename T>
void qhUniqueQList(QList<T>& list)
{
    for(int i=list.size()-1; i>=0; --i)
    {
        const T& v = list[i];
        for(int j=i-1; j>=0; --j)
        {
            if (v == list[j])
            {
                list.removeAt(i);
                break;
            }
        }
    }
}

/**
* @brief 把 QList 中所有元素值 是 befor的替换成 after
*
* 其他元素的顺序不变
* 比如，传入 list是 “2” “1” “3” “1” “0”，调用 qhQListReplace(list, "1", "5"),
	则 list 变为 “2” “5” “3” “5” “0”

	若有替换发生 返回真，否则返回假
* \test HelpQList
*/
template<typename T>
bool qhQListReplace(QList<T>& list, const T& befor, const T& after)
{
	assert(befor != after);

	bool ret = false;
	int count = list.count();
	for (int i=0; i<count; ++i)
	{
		if (list[i] == befor)
		{
			ret = true;
			list[i] = after;
		}
	}

	return ret;

}

/**
 * @brief 设置定时器，在 h 时 m分 s秒发作，返回　timer id
 *      调用 实现 pObj->startTimer
 * @param h
 * @param m
 * @param s
 * @return 0,失败
 */
int qhStartTimerAtTime(QObject* pObj, const QTime& runTime);
inline int qhStartTimerAtTime(QObject* pObj, int h, int m, int s = 0)
{
   QTime runTime(h, m, s);
   return qhStartTimerAtTime(pObj, runTime);
}


/** \name 将枚举类型转化为 QMap<int, QString>，方便调试
 *  实际 使用 QH_GET_ENUM_MAP 或者 qhGetEnumMap 要很方便
 * @{
  */


#ifndef E_I
#define E_I(enumItem) (enumItem), (#enumItem)
#endif

#ifndef QH_GET_CODE
#define QH_GET_CODE(...) \
    QString(#__VA_ARGS__)
#endif

/**
  为了方便调试
 * 得到 枚举类型对应的 字符串形式 到 QMap<int, QString> 类型，
 *如 enum Type {

        None = 0,                               // invalid event
        Timer = 1,                              // timer event
        MouseButtonPress = 2,                   // mouse button pressed
        MouseButtonRelease = 3,                 // mouse button released
//            #ifdef QT_KEYPAD_NAVIGATION
//                    EnterEditFocus = 150,                   // enter edit mode in keypad navigation
//            #endif
        };
 * @param code 代码
 * @param map，对于 解析不出来的枚举值 可以预先 从 map传入
 * @return
 * \note 配合 QH_GET_CODE 使用。 支持 代码中对注释的处理，但不支持对 预处理的处理,没法支持对宏的处理.搭配宏使用示例如下
  QMap<int, QString> map3 = qhGetEnumMap(
                QH_GET_CODE(
    enum Policy {
        Fixed = 0,
        Minimum = QSizePolicy::GrowFlag,
        Maximum = QSizePolicy::ShrinkFlag,
        Preferred = QSizePolicy::GrowFlag | QSizePolicy::ShrinkFlag
                    }),
                QH_GET_ENUM_MAP(E_I(QSizePolicy::Minimum),
                                 E_I(QSizePolicy::Maximum),
                                 E_I(QSizePolicy::Preferred) );
   \note 目前在解析code时只支持 直接给枚举赋值、不赋值、直接引用上个枚举值得情况，如
       enum Policy {
            E1,
            E2 = 4,
            E3,
            E4 = E2}， 其他形式 如
       enum Policy {
            E1 = 1+2,
            E2,
            E3 = E2 | E1}, 是解析不出来的的，只能通过 map 参数传入，
       当传入的 map 的值 与 解析的值冲突时，以传入map的为准
 */
QMap<int, QString> qhGetEnumMap(const QString &code,
                                QMap<int, QString> &map = QMap<int, QString>());

/**
 * 得到 枚举类型对应的 字符串形式 到 QMap<int, QString> 类型，
 * 可变参数是 int, const char * 类型的序列，键值对达到 count 个或 值得类型为 “0” 停止。
 * 方便起见 配合宏可以这样用 qhGetEnumMap(INT_MAX,
                        E_I(QSizePolicy::Maximum),
                        E_I(QSizePolicy::Preferred), E_I(0))
 *
 * @param count 枚举值的个数
 * @return
 */
QMap<int, QString> qhGetEnumMap(int count, ...);



/**
  配合 E_I 使用，将每个枚举值 添加到 map中 并返回map，示例如下
    QH_GET_ENUM_MAP(E_I(QSizePolicy::Minimum),
                     E_I(QSizePolicy::Maximum),
                     E_I(QSizePolicy::Preferred))
  */
#ifndef QH_GET_ENUM_MAP
#define QH_GET_ENUM_MAP(...) \
    qhGetEnumMap(INT_MAX, __VA_ARGS__, E_I(0))
#endif

/** @}
  */

#endif // QHELPFUNCTION_H
