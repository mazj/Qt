/**
  \file qHelpFunction.h
  \brief ��װ qt�� qtCore��qtXmlһЩ���� �������У�Ӧ�ó�����Կ�ݵ��ã�qt�İ���������qh��ͷ

  \note Ϊ�˲���һ���ض������������ң� ÿ������������ һ�� \\test ��ǩ��һ�������Ϊ Help�ؼ�
  \test Ϊ�˲���һ���ض������������ң� ÿ������������ һ�� \\test ��ǩ��һ�������Ϊ Help�ؼ�
  \author �ﺣ��
  \date 2014.2.24  ����
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
  Q_ASSERT �� �� debug ʱʲôҲ���ɣ�
  QH_VERIFY �� �� debug ʱ ��Ȼ��ֵ�������ж�
  */
#ifdef QT_NO_DEBUG
#define QH_VERIFY(explore) explore
#else
#define QH_VERIFY(explore) Q_ASSERT(explore)
#endif


/**
 * @brief ����c�����е� �ַ���
 * c c++ �е��ַ����� ����ת���ַ����ú����Ĺ����� ��ת���ַ�����ʽ ת���� �������ַ���
 * \note ֻ�ܴ����ֽڵ�ת���ַ�
 * �磺���� cCodeStr "17766\noo\rthth\t\\"���� \n \r \t \\ ���ᱻ�滻��ʵ���ַ�
 * @param cCodeStr
 */
QString& qhConvertCCodeString(QString &cCodeStr);

/**
 * @brief is16Number �ж�QChar �Ƿ��� 16 ���Ƶ����ֻ���ĸ
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
 *  �ж��Ƿ��� �ϸ�� 16���� ���ֽڵ���ʽ
 *  qhQStringIs16Bytes("0x00d8", 2) ������
 *  qhQStringIs16Bytes("0xd8", 2) ���ؼ�
 * @param str
 * @param byteCount �����ֽ�
 * @return
 * \test HelpQString
 */
bool qhQStringIs16Bytes(const QString& str, int byteCount);

/**
 * @brief qhQStringTo16Int
 *  ���ַ���ת����16���Ƶ����֣��ַ����Ƿ��� 0x �� 0X��ͷ������
 * qhQStringTo16Int("0xd2") ���� 0xd2
 * qhQStringTo16Int("d2") ���� 0xd2
 * qhQStringTo16Int("dR") ת��ʧ��
 * @param str
 * @param ret ת���Ƿ�ɹ�
 * @return
 *  * \test HelpQString
 */
int qhQStringTo16Int(const QString& str, bool *ret = NULL);

/**
 * @brief qhQCharIs8Number �ж�QChar �Ƿ��� 8 ���Ƶ�����
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
 * @brief qhQCharToNumber ��QCharת�������֣���������
 * @param c
 * @param base �����ƣ�Ŀǰֻ�� 16 �� 10���� 8����
 * @return ����ת���ɹ�������ʧ�ܷ��� -1
 *  * \test HelpQChar
 */
int qhQCharToNumber(const QChar& c, int base = 10);



/**
 * @brief qhString2Int �� QString ת���� int
 * �� qhString2Int(QString("qsw23rf"),1) ��ת��ʧ��
 * qhString2Int(QString("qsw23rf"),3) ��ת���ɹ�������23��end����5
 * qhString2Int(QString("qsw23rf"),4) ��ת���ɹ�������4��end����5
 * qhString2Int(QString("qsw 23rf"),3) ��ת���ɹ�������23��end����6
 *
 * @param str
 * @param successful [out] ת���Ƿ�ɹ�
 * @param from      ��ʼת����λ��
 * @param end [out] ת������λ��
 * @param base ���ٽ���,Ŀǰֻ�ܴ�10 �� 16 �� 8
 * @return  ת���ɵ����֣�ת��ʧ�ܷ��� -1

 * \test HelpQString
 */
int qhQString2Int(const QString& str, int from=0, int base = 10, int* end=NULL, bool *successful = NULL);

/**
 * �ҵ� QString str �� ��һ�еĽ�βλ��
 * @param str
 * @param from �ӵڼ����ַ���ʼ����
 * @return ��βλ�ã�û�ҵ�����-1
 *
 *  ע��window �Ļ��� �ڴ��̴������ǻس��������ַ���
 * ���� ���ı���ʽ��ʱ���о�ֻ��һ�����з�
 * \test HelpQString
 */
int qhQStringFindLineEndPos(const QString & str, int from = 0);

/**
 * ���غ���
 * @param [in][out]code
 */
void qhRemoveExegesisInCode_(QString &code);

/**
 * ȥ�� c c++���� code �� ��ע��
 * @param code
 * @return ȥ�� ע�� ��Ĵ���
 * \note ȥ��ע�ͺ���ַ��� ��֮ǰ������һ��.
 *       ֻ�ܴ����ʽ��ȷ�� c c++���룬��ʽ����ȷ�Ŀ��ܻ����.
 *       û�������
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
 * ��ݺ��� �õ��ļ� filePath ����������
 * @param filePath �ļ�·��
 * @param content  ��������ļ�����
 * @return �����ļ�����
 * \test HelpQFile
 */
QString& qhReadQFileString(const QString& filePath, QString& content);

/**
 * @brief qhWriteQFileString �� content ����д�� �ļ�filePath�У�
 * �� filePathû���򴴽�����filePath�Ѿ��У������ԭ������
 * @param filePath
 * @param content
 * @return
 * \test HelpQFile
 */
bool qhWriteQFileString(const QString& filePath, const QString &content,
                        QTextCodec *codec = NULL);

/**
	�ж�QList ���Ƿ����ظ�Ԫ�ء�
	�����򷵻��棬 repeat ��� ��һ���ظ�Ԫ�ص�λ��
	û�з��ؼ�
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
 * @brief ȥ�� QList �е��ظ�Ԫ��
 *
 * ȥ�� QList �е��ظ�Ԫ�أ����ظ�Ԫ�ص�˳�򲻱�.�ظ�Ԫ��ȥ���󲿵�Ԫ�ء�����
 * ���� list�� ��2�� ��1�� ��3�� ��1�� ��0�����򴫳��� ��2�� ��1�� ��3�� ��0��
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
* @brief �� QList ������Ԫ��ֵ �� befor���滻�� after
*
* ����Ԫ�ص�˳�򲻱�
* ���磬���� list�� ��2�� ��1�� ��3�� ��1�� ��0�������� qhQListReplace(list, "1", "5"),
	�� list ��Ϊ ��2�� ��5�� ��3�� ��5�� ��0��

	�����滻���� �����棬���򷵻ؼ�
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
 * @brief ���ö�ʱ������ h ʱ m�� s�뷢�������ء�timer id
 *      ���� ʵ�� pObj->startTimer
 * @param h
 * @param m
 * @param s
 * @return 0,ʧ��
 */
int qhStartTimerAtTime(QObject* pObj, const QTime& runTime);
inline int qhStartTimerAtTime(QObject* pObj, int h, int m, int s = 0)
{
   QTime runTime(h, m, s);
   return qhStartTimerAtTime(pObj, runTime);
}


/** \name ��ö������ת��Ϊ QMap<int, QString>���������
 *  ʵ�� ʹ�� QH_GET_ENUM_MAP ���� qhGetEnumMap Ҫ�ܷ���
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
  Ϊ�˷������
 * �õ� ö�����Ͷ�Ӧ�� �ַ�����ʽ �� QMap<int, QString> ���ͣ�
 *�� enum Type {

        None = 0,                               // invalid event
        Timer = 1,                              // timer event
        MouseButtonPress = 2,                   // mouse button pressed
        MouseButtonRelease = 3,                 // mouse button released
//            #ifdef QT_KEYPAD_NAVIGATION
//                    EnterEditFocus = 150,                   // enter edit mode in keypad navigation
//            #endif
        };
 * @param code ����
 * @param map������ ������������ö��ֵ ����Ԥ�� �� map����
 * @return
 * \note ��� QH_GET_CODE ʹ�á� ֧�� �����ж�ע�͵Ĵ�������֧�ֶ� Ԥ����Ĵ���,û��֧�ֶԺ�Ĵ���.�����ʹ��ʾ������
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
   \note Ŀǰ�ڽ���codeʱֻ֧�� ֱ�Ӹ�ö�ٸ�ֵ������ֵ��ֱ�������ϸ�ö��ֵ���������
       enum Policy {
            E1,
            E2 = 4,
            E3,
            E4 = E2}�� ������ʽ ��
       enum Policy {
            E1 = 1+2,
            E2,
            E3 = E2 | E1}, �ǽ����������ĵģ�ֻ��ͨ�� map �������룬
       ������� map ��ֵ �� ������ֵ��ͻʱ���Դ���map��Ϊ׼
 */
QMap<int, QString> qhGetEnumMap(const QString &code,
                                QMap<int, QString> &map = QMap<int, QString>());

/**
 * �õ� ö�����Ͷ�Ӧ�� �ַ�����ʽ �� QMap<int, QString> ���ͣ�
 * �ɱ������ int, const char * ���͵����У���ֵ�Դﵽ count ���� ֵ������Ϊ ��0�� ֹͣ��
 * ������� ��Ϻ���������� qhGetEnumMap(INT_MAX,
                        E_I(QSizePolicy::Maximum),
                        E_I(QSizePolicy::Preferred), E_I(0))
 *
 * @param count ö��ֵ�ĸ���
 * @return
 */
QMap<int, QString> qhGetEnumMap(int count, ...);



/**
  ��� E_I ʹ�ã���ÿ��ö��ֵ ��ӵ� map�� ������map��ʾ������
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
