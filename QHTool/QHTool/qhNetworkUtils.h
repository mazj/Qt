#ifndef __NETWORK_UTILS_H__
#define __NETWORK_UTILS_H__

class QValidator;
class QObject;
class QString;

namespace qhNetwork
{

//////转换一个二进制的数值为十六进制字符串
//template <typename T>
//QString hexMacString(const T _value)
//{
//	return hexMacString((const quint8 *) &_value, sizeof(T));
//}

////转换一个MAC地址为十六进制字符串 01-23-45-67-89-AB-EF
QString hexMacString(const char *_mac, const size_t _size = 6);

QString hexMacString(const unsigned char *_mac, const size_t _size = 6);

QString timeZone(const short _second);

////转换一个MAC地址的一位为十六进制字符串
QString hexMacChar(const unsigned char _char);

////获取IP地址的最后一个点后的值
QString lastValueOfIP(const QString& _ip);

////验证IP是否有效
bool isValidIP(const QString& _ip);

////马栋 20120702，检查端口值是否为有效值
bool isValidPort(const QString& _port);

//////马栋 20120628，创建一个新的IP正则表达式验证器
//QValidator *newIPValidator(QObject *_parent);
//
//////马栋 20120702，创建一个新的端口正则表达式验证器
//QValidator *newPortValidator(QObject *_parent);

}

#endif
