#pragma once

#include <QString>
#include <QMap>

class QTextCodec;

/**
	ini格式文件注释类
	主要功能是 保存 ini文件的注释，在需要的时候 把这些保存的注释 填写到 ini文件中。
	可以配合 ini格式的 QSettings使用，因为 ini格式的 QSettings 是没有注释的。

    \bug 1.在填充注释信息时，若已经有了同样的注释信息，仍然会填充注释信息。
        2.若在 getNoteFromIniFile 时 ini文件形如：
 ; note1 开始
note1=123  ;也是注释1
        在 fillNoteToIniFile 时文件变成了
[General]
note1=123
        则不能正确填充注释
*/
class IniNote
{
public:
	IniNote(void);
	~IniNote(void);

	/************************************************************************//**
    * 设置 ini文件编码方式, 默认是 QTextCodec::codecForLocale()
	****************************************************************************/
	void setIniTextCodec(QTextCodec *pTextCodec);

	/************************************************************************//**
	* 从ini文件获取注释                                                                     
	****************************************************************************/
	bool getNoteFromIniFile(const QString &file);

	/************************************************************************//**
	*填充注释到 ini 文件, 带有注释的文件存在 outFileName                                                                   
	****************************************************************************/
	bool fillNoteToIniFile(const QString &file, const QString & outFileName);

	/************************************************************************//**
	* 填充注释到 ini 文件 file                                                                     
	****************************************************************************/
	bool fillNoteToIniFile(const QString &file);

private:
	QTextCodec *m_pTextCodec;
	typedef QMap<QString, QString> StrQMap;
    /**
 ; SystemCfg 开始
[SystemCfg]  ;也是注释1
;IED名称
IEDname=CSN15B04  ;也是注释2
;逻辑设备名称
LD_name=MUSV

对每节 [] 级别的注释 放在 m_externalMap中,
如 m_externalMap["[SystemCfg]"] = " ; SystemCfg 开始"
对每节内的注释 放在 m_internalMap 中,
如 m_internalMap["[SystemCfg]"]["IEDname"] = ";IED名称"

对于一行内 前部是内容后部是注释的情况,在 map的key值中添加 ";"加以区别,如
m_externalMap["[SystemCfg];"] = ";也是注释1"
m_internalMap["[SystemCfg]"]["IEDname;"] = ";也是注释2"
     */
	StrQMap  m_externalMap;
	QMap<QString, StrQMap> m_internalMap;

};
