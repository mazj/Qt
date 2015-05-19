#include "qhNetworkUtils.h"
//#include "reg_exp_validator.h"
#include <qglobal.h>
#include <qobject.h>
#include <qstring.h>
#include <qregexp.h>
//#include <qvalidator.h>
//#include <QRegExpValidator>

namespace qhNetwork
{

static const QString REG_EXP_IP("^((25[0-5]|2[0-4]\\d|1?\\d?\\d\\.){3}(25[0-5]|2[0-4]\\d|1?\\d?\\d))$");
static const QString REG_EXP_PORT("^([0-9]|[1-9]\\d|[1-9]\\d{2}|[1-9]\\d{3}|[1-5]\\d{4}|6[0-4]\\d{3}|65[0-4]\\d{2}|655[0-2]\\d|6553[0-5])$");

QString hexMacString(const char *_mac, const size_t _size)
{
	return hexMacString((const unsigned char *) _mac, _size);
}

QString hexMacString(const unsigned char *_mac, const size_t _size)
{
	//Q_ASSERT(_mac != NULL);
	if (!(_mac != NULL))
	{
		return QString();
	}

	//Q_ASSERT(_size > 0);
	if (!(_size > 0))
	{
		return QString();
	}

	QString _text(hexMacChar(_mac[0]));
	for (const unsigned char *_begin = _mac + 1, *_end = _mac + _size; _begin != _end; ++_begin)
	{  
	
	   _text +=QString("-%1").arg(hexMacChar(*_begin));
		
	}

	return _text;
}

////ת��һ��MAC��ַ��һλΪʮ�������ַ���
QString hexMacChar(const unsigned char _char)
{
	char _buffer[4];
	memset(_buffer, 0, sizeof(_buffer));
	sprintf(_buffer, "%02X", _char);
	return _buffer;
}

////��ȡIP��ַ�����һ������ֵ
QString lastValueOfIP(const QString& _ip)
{
	//Q_ASSERT(isValidIP(_ip));
	return _ip.mid(_ip.lastIndexOf('.') + 1, 3);
}

////��֤IP�Ƿ���Ч
bool isValidIP(const QString& _ip)
{
	////�� 20120525����֤IP�Ƿ���Ч
	static const QRegExp _regExp((REG_EXP_IP));
	return _regExp.exactMatch(_ip);
}

////�� 20120702�����˿�ֵ�Ƿ�Ϊ��Чֵ
bool isValidPort(const QString& _port)
{
	static const QRegExp _regExp((REG_EXP_PORT));
	return _regExp.exactMatch(_port);
}

//////�� 20120628������һ���µ�IP������ʽ��֤��
//QValidator *newIPValidator(QObject *_parent)
//{
//	return new QRegExpValidator(QRegExp(REG_EXP_IP), _parent);
//}
//
//////�� 20120702������һ���µĶ˿�������ʽ��֤��
//QValidator *newPortValidator(QObject *_parent)
//{
//	return new QRegExpValidator(QRegExp(REG_EXP_PORT), _parent);
//}

}	//end qhNetwork

//end network_utils.cpp
