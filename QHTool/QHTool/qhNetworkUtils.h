#ifndef __NETWORK_UTILS_H__
#define __NETWORK_UTILS_H__

class QValidator;
class QObject;
class QString;

namespace qhNetwork
{

//////ת��һ�������Ƶ���ֵΪʮ�������ַ���
//template <typename T>
//QString hexMacString(const T _value)
//{
//	return hexMacString((const quint8 *) &_value, sizeof(T));
//}

////ת��һ��MAC��ַΪʮ�������ַ��� 01-23-45-67-89-AB-EF
QString hexMacString(const char *_mac, const size_t _size = 6);

QString hexMacString(const unsigned char *_mac, const size_t _size = 6);

QString timeZone(const short _second);

////ת��һ��MAC��ַ��һλΪʮ�������ַ���
QString hexMacChar(const unsigned char _char);

////��ȡIP��ַ�����һ������ֵ
QString lastValueOfIP(const QString& _ip);

////��֤IP�Ƿ���Ч
bool isValidIP(const QString& _ip);

////�� 20120702�����˿�ֵ�Ƿ�Ϊ��Чֵ
bool isValidPort(const QString& _port);

//////�� 20120628������һ���µ�IP������ʽ��֤��
//QValidator *newIPValidator(QObject *_parent);
//
//////�� 20120702������һ���µĶ˿�������ʽ��֤��
//QValidator *newPortValidator(QObject *_parent);

}

#endif
