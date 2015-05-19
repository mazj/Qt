// �������Ⱑ

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
    // ���ļ�
	QFile file(fileName); 
	if (!file.open(QIODevice::ReadOnly)) 
	{ 
		qDebug()<<"readIniComment open"<<fileName<<"failed!:"<<file.error(); 
		return false; 
	} 

    // ���map
	m_externalMap.clear();
	m_internalMap.clear();

	QTextStream inStream(&file); 
	inStream.setCodec(m_pTextCodec); 
	QString data;
    QString note;   //ע��
	bool ok = true;
    // ָ��ǰ��map
	StrQMap *pStrMap = &m_externalMap;

    // һ��һ�еĶ�ȡ����, ��ȡע��
	while (!inStream.atEnd()) 
	{ 
		data = inStream.readLine(); 
        QString trimmed = data.trimmed(); //ȥ���ַ�����ʼ�ͽ����Ŀհ�

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
            // ���� һ���� ������������ע�͵����
            int index = trimmed.indexOf(";");
            QString key = trimmed.left(index);
            key = key.trimmed();
            QString lineNote;
            if (index != -1)
            {
                lineNote = trimmed.right(trimmed.length()-index);
            }

            // ��ȡ����ע��
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

            // ��ȡһ���� ������������ע�͵�����µ�ע��
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
    // ׼�������ļ�
	QFile inFile(fileName); 
	if (!inFile.open(QIODevice::ReadOnly|QIODevice::Text)) 
	{ 
		qDebug()<<"WriteIniComment open"<<fileName<<"failed!"; 
		return false; 
	} 

    // ׼������ļ�
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

    // һ��һ�ж�ȡ�ļ������ע��
	while (!inStream.atEnd()) 
	{ 
		data = inStream.readLine(); 
		QString trimmed = data.trimmed();
        // ���� һ���� ������������ע�͵����
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
            // �������ע��
            if(m_externalMap.contains(key))
                outStream << m_externalMap.value(key) << "\n";

            //// ���һ���� ������������ע�͵�����µ�ע��
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

            //// ���һ���� ������������ע�͵�����µ�ע��
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
