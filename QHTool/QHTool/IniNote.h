#pragma once

#include <QString>
#include <QMap>

class QTextCodec;

/**
	ini��ʽ�ļ�ע����
	��Ҫ������ ���� ini�ļ���ע�ͣ�����Ҫ��ʱ�� ����Щ�����ע�� ��д�� ini�ļ��С�
	������� ini��ʽ�� QSettingsʹ�ã���Ϊ ini��ʽ�� QSettings ��û��ע�͵ġ�

    \bug 1.�����ע����Ϣʱ�����Ѿ�����ͬ����ע����Ϣ����Ȼ�����ע����Ϣ��
        2.���� getNoteFromIniFile ʱ ini�ļ����磺
 ; note1 ��ʼ
note1=123  ;Ҳ��ע��1
        �� fillNoteToIniFile ʱ�ļ������
[General]
note1=123
        ������ȷ���ע��
*/
class IniNote
{
public:
	IniNote(void);
	~IniNote(void);

	/************************************************************************//**
    * ���� ini�ļ����뷽ʽ, Ĭ���� QTextCodec::codecForLocale()
	****************************************************************************/
	void setIniTextCodec(QTextCodec *pTextCodec);

	/************************************************************************//**
	* ��ini�ļ���ȡע��                                                                     
	****************************************************************************/
	bool getNoteFromIniFile(const QString &file);

	/************************************************************************//**
	*���ע�͵� ini �ļ�, ����ע�͵��ļ����� outFileName                                                                   
	****************************************************************************/
	bool fillNoteToIniFile(const QString &file, const QString & outFileName);

	/************************************************************************//**
	* ���ע�͵� ini �ļ� file                                                                     
	****************************************************************************/
	bool fillNoteToIniFile(const QString &file);

private:
	QTextCodec *m_pTextCodec;
	typedef QMap<QString, QString> StrQMap;
    /**
 ; SystemCfg ��ʼ
[SystemCfg]  ;Ҳ��ע��1
;IED����
IEDname=CSN15B04  ;Ҳ��ע��2
;�߼��豸����
LD_name=MUSV

��ÿ�� [] �����ע�� ���� m_externalMap��,
�� m_externalMap["[SystemCfg]"] = " ; SystemCfg ��ʼ"
��ÿ���ڵ�ע�� ���� m_internalMap ��,
�� m_internalMap["[SystemCfg]"]["IEDname"] = ";IED����"

����һ���� ǰ�������ݺ���ע�͵����,�� map��keyֵ����� ";"��������,��
m_externalMap["[SystemCfg];"] = ";Ҳ��ע��1"
m_internalMap["[SystemCfg]"]["IEDname;"] = ";Ҳ��ע��2"
     */
	StrQMap  m_externalMap;
	QMap<QString, StrQMap> m_internalMap;

};
