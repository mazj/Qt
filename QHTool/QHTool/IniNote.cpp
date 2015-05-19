// 还有问题啊

#include <QFile>
#include <QString> 
#include <QVariant> 
#include <QDebug>
#include <QTextStream>
#include <QTextCodec>

#include "IniNote.h"

IniNote::IniNote(void)
{
	m_pTextCodec = QTextCodec::codecForLocale();
}

IniNote::~IniNote(void)
{
}

bool IniNote::getNoteFromIniFile( const QString &fileName )
{
    // 打开文件
	QFile file(fileName); 
	if (!file.open(QIODevice::ReadOnly)) 
	{ 
		qDebug()<<"readIniComment open"<<fileName<<"failed!:"<<file.error(); 
		return false; 
	} 

    // 清空map
	m_externalMap.clear();
	m_internalMap.clear();

	QTextStream inStream(&file); 
	inStream.setCodec(m_pTextCodec); 
	QString data;
    QString note;   //注释
	bool ok = true;
    // 指向当前的map
	StrQMap *pStrMap = &m_externalMap;

    // 一行一行的读取数据, 获取注释
	while (!inStream.atEnd()) 
	{ 
		data = inStream.readLine(); 
        QString trimmed = data.trimmed(); //去除字符串开始和结束的空白

        if(trimmed.isEmpty())
		{ 
			continue; 
		} 
        else if(/*trimmed[0]== QChar('#') ||*/ trimmed[0]== QChar(';'))
		{ 
			note += "\n" + data; 
#ifdef LZM_DEBUG 
			qDebug()<<"line"<<line<<"text"<<data; 
#endif 
		} 
		else 
		{ 
            // 处理 一行中 既有内容又有注释的情况
            int index = trimmed.indexOf(";");
            QString key = trimmed.left(index);
            key = key.trimmed();
            QString lineNote;
            if (index != -1)
            {
                lineNote = trimmed.right(trimmed.length()-index);
            }

            // 获取整行注释
			if (!note.isEmpty())
			{
                if (key[0] == QChar('['))
				{
                    m_externalMap[key] = note;
                    m_internalMap[key] = StrQMap();
                    pStrMap = &m_internalMap[key];
				}
				else
				{
                    (*pStrMap)[key.left(key.indexOf("="))] = note;
				}
				note.clear();
			}
            else
            {
                if (key[0] == QChar('['))
                {
                    m_internalMap[key] = StrQMap();
                    pStrMap = &m_internalMap[key];
                }
            }

            // 获取一行中 既有内容又有注释的情况下的注释
            if (!lineNote.isEmpty())
            {
                if (key[0] == QChar('['))
                {
                    m_externalMap[key+";"] = lineNote;
                }
                else
                {
                    (*pStrMap)[key+";"] = lineNote;
                }
            }
//			else
//			{
//                if (key[0] == QChar('['))
//				{
//                    m_internalMap[key] = StrQMap();
//                    pStrMap = &m_internalMap[key];
//				}
//			}
        }
	} 

	return ok;
}

bool IniNote::fillNoteToIniFile( const QString &fileName, const QString & outFileName)
{
    // 准备输入文件
	QFile inFile(fileName); 
	if (!inFile.open(QIODevice::ReadOnly|QIODevice::Text)) 
	{ 
		qDebug()<<"WriteIniComment open"<<fileName<<"failed!"; 
		return false; 
	} 

    // 准备输出文件
	QFile outfile(outFileName); 
	if (!outfile.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) 
	{ 
		qDebug()<<"open"<<outFileName<<"failed!"; 
		return false; 
	} 

	QTextStream inStream(&inFile); 
	inStream.setCodec(m_pTextCodec); 

	QTextStream outStream(&outfile); 
	outStream.setCodec(m_pTextCodec); 

	QString data; 
	bool ok = true; 
	StrQMap *pStrMap = &m_externalMap;

    // 一行一行读取文件，添加注释
	while (!inStream.atEnd()) 
	{ 
		data = inStream.readLine(); 
		QString trimmed = data.trimmed();
        // 处理 一行中 既有内容又有注释的情况
        int index = trimmed.indexOf(";");
        QString key = trimmed.left(index);
        key = key.trimmed();

		if(trimmed.isEmpty()) 
		{ 
			outStream <<"\n"; 
			continue;
		} 
		else if (/*trimmed[0]== QChar('#') ||*/ trimmed[0]== QChar(';'))
		{ 
			outStream << data <<"\n"; 
		}
		else if (trimmed[0] == QChar('['))
		{
            // 添加整行注释
            if(m_externalMap.contains(key))
                outStream << m_externalMap.value(key) << "\n";

            //// 添加一行中 既有内容又有注释的情况下的注释
            if (m_externalMap.contains(key+";"))
            {
                outStream << data << m_externalMap.value(key+";") << "\n";
            }
            else
            {
                outStream << data << "\n";
            }

            pStrMap = &m_internalMap[key];
		}
		else
		{
            key = key.left(key.indexOf("="));
            if ( pStrMap->contains(key) )
                outStream << pStrMap->value( key ) << "\n";

            //// 添加一行中 既有内容又有注释的情况下的注释
            if (pStrMap->contains(key+";"))
            {
                outStream << data << pStrMap->value(key+";") << "\n";
            }
            else
            {
                outStream << data << "\n";
            }
		}
	} 

	inFile.close(); 
	outfile.close(); 
	// 

	//QFile::remove(fileName); 
	//qDebug()<<"remove"<<fileName; 
	//QFile::rename(outFileName, fileName); 
	//qDebug()<<"rename"<<outFileName<<"to"<<fileName; 

	return ok; 

}

bool IniNote::fillNoteToIniFile( const QString &file )
{
	QString outFile(file+".out");
	int num = 0;
	bool ret = false;
	
	while ( QFile::exists(outFile) )
	{
		outFile += QString::number(++num);
	}
	
	if ( fillNoteToIniFile(file, outFile) )
	{
		QFile::remove(file);
		ret = QFile::rename(outFile, file);
		if ( !ret )
			qDebug()<<"rename "<<outFile<<" to "<<file << " fail!"; 
		return ret;
	}
	else
	{
		return false;
	}

	//QFile::remove(fileName); 
	//qDebug()<<"remove"<<fileName; 
	//QFile::rename(outFileName, fileName); 
	//qDebug()<<"rename"<<outFileName<<"to"<<fileName; 
}

void IniNote::setIniTextCodec( QTextCodec *pTextCodec )
{
	Q_ASSERT(pTextCodec);
	m_pTextCodec = pTextCodec;
}
