#include <exception>
#include <stdarg.h>
#include <assert.h>
//：#include <stdarg.h>
#include <QtGlobal>
#include <QtCore>
#undef COMPILE_QH_DEBUGMSG
#include "QHToolConfig.h"
#include "qhDebugMsg.h"

QFile *s_pOutPutFile = NULL;

#ifdef QHTOOL_QT5

void ghMessageOutputToFile(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    if (!s_pOutPutFile)
    {
        return;
    }

    char localMsg[1024];
    localMsg[1023] = '\0';
    switch (type) {
    case QtDebugMsg:
        _snprintf(localMsg, 1023, "Debug: %s (%s:%u, %s)\n", msg.toLocal8Bit().constData(), context.function, context.line, context.file);
        break;
    case QtWarningMsg:
        _snprintf(localMsg, 1023, "Warning: %s (%s:%u, %s)\n", msg.toLocal8Bit().constData(), context.function, context.line, context.file);
        break;
    case QtCriticalMsg:
        _snprintf(localMsg, 1023, "Critical: %s (%s:%u, %s)\n", msg.toLocal8Bit().constData(), context.function, context.line, context.file);
        break;
    case QtFatalMsg:
        _snprintf(localMsg, 1023, "Fatal: %s (%s:%u, %s)\n", msg.toLocal8Bit().constData(), context.function, context.line, context.file);
        break;
    }

     s_pOutPutFile->write(localMsg);
     s_pOutPutFile->flush();

     if (type == QtFatalMsg)
#ifdef _DEBUG
        assert(!"type == QtFatalMsg");
#else
         abort();
#endif
}

#else

void ghMessageOutputToFile(QtMsgType type, const char *msg)
{
    if (!s_pOutPutFile)
    {
        return;
    }

    switch (type) {
    case QtDebugMsg:
        s_pOutPutFile->write("Debug: ");
        break;
    case QtWarningMsg:
        s_pOutPutFile->write("Warning: ");
        break;
    case QtCriticalMsg:
        s_pOutPutFile->write("Critical: ");
        break;
    case QtFatalMsg:
         s_pOutPutFile->write("Fatal: ");
        break;
    }

    s_pOutPutFile->write(msg);
    s_pOutPutFile->write("\n");
    s_pOutPutFile->flush();

//    if (type == QtFatalMsg)
////        abort();
//        assert(0);

}

#endif

bool qhInstallMsgHandler_file(const QString & file, const QString & softwareName)
{
    if (!s_pOutPutFile)
    {
        s_pOutPutFile = new QFile(file);
        s_pOutPutFile->open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
        if (s_pOutPutFile->size() > 1024*1024*2) //2M
        {
            bool ret = s_pOutPutFile->resize(0);
            (void)ret;
            s_pOutPutFile->seek(s_pOutPutFile->size());
        }
        s_pOutPutFile->write((QString("\n-----------") + softwareName + " run-------------\n")
                             .toLocal8Bit());
        s_pOutPutFile->write(QDateTime::currentDateTime().toString().toLocal8Bit());
        s_pOutPutFile->write("\n");
#ifdef QHTOOL_QT5
        qInstallMessageHandler(ghMessageOutputToFile);
#else
        qInstallMsgHandler(ghMessageOutputToFile);
#endif

        return true;
    }

    return false;
}


#define TRACKER_BEGIN "TrackerBegin"
#define TRACKER_END "TrackerEnd"
#define TRACKER "ITracker"

/**
 * 跟踪器接口，可以有不同类型的跟踪器
 */
class ITracker
{
public:
    static int increaseRef(ITracker *t);
    static int decreaseRef(ITracker * & t);

    virtual bool flush() { return true; }
    virtual void writeText(const QString & text) = 0;

protected:
    //  禁止复制
    ITracker(const ITracker &);
    ITracker & operator =(const ITracker &);

    ITracker(const QString & title);
    virtual ~ITracker();

    //因为 writeBeginElement writtEndElement 的调用次数必须相同，防止外部调用次数不一致
    // 只允许 TrackElement TrackHelper 调用
    friend class TrackHelper;
    friend class TrackElement;
    virtual void writeBeginElement(const QString & element,
                           const QMap<QString, QString> & attribute = QMap<QString, QString>()) = 0;
    virtual void writtEndElement(const QString & element, bool newLine = false) = 0;

protected:    
    QString m_title;
    int m_refCount;
};

int ITracker::increaseRef(ITracker *t)
{
    t->m_refCount++;
    return t->m_refCount;
}

int ITracker::decreaseRef(ITracker *&t)
{
    t->m_refCount--;
    int n = t->m_refCount;
    if ( t->m_refCount == 0)
    {
        delete t;
        t = NULL;
    }
    return n;
}


ITracker::ITracker(const QString &title)
    : m_title(title),
      m_refCount(0)
{
}

ITracker::~ITracker()
{
}

class TrackerForXmlFile : public ITracker
{
public:
    virtual bool flush() { return m_outPutFile.flush(); }
    virtual void writeText(const QString & text) { m_outPutFile.write(text.toLocal8Bit()); }

protected:
    TrackerForXmlFile(const QString & title, const QString & file);
    virtual ~TrackerForXmlFile();

    //因为 writeBeginElement writtEndElement 的调用次数必须相同，防止外部调用次数不一致
    // 只允许 TrackElement TrackHelper 调用
    friend class TrackHelper;
    friend class TrackElement;
    virtual void writeBeginElement(const QString & element,
                           const QMap<QString, QString> & attribute = QMap<QString, QString>());
    virtual void writtEndElement(const QString & element, bool newLine = false);

protected:
    QFile m_outPutFile;
    QString m_indent;
};



TrackerForXmlFile::TrackerForXmlFile(const QString &title, const QString &file)
    : ITracker(title),
      m_outPutFile(file),
      m_indent()
{
    bool ret;
    m_outPutFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
    if (m_outPutFile.size() > 1024*1024*2) //2M
    {
        ret = m_outPutFile.resize(0);
        m_outPutFile.seek(m_outPutFile.size());
    }

//    m_outPutFile.write("\n");

    QMap<QString, QString> attribute;
    attribute.insert("time", QDateTime::currentDateTime().toString());
    writeBeginElement(m_title, attribute);
}

TrackerForXmlFile::~TrackerForXmlFile()
{
    writtEndElement(m_title, true);
    m_outPutFile.write("\n");
    m_outPutFile.flush();
    m_outPutFile.close();
}



void TrackerForXmlFile::writeBeginElement(const QString &element,
                                const QMap<QString, QString> & attribute)
{
    m_outPutFile.write("\n");
    m_indent.append('\t');
    m_outPutFile.write(m_indent.toLocal8Bit());
    m_outPutFile.write(("<" + element).toLocal8Bit());
    if (!attribute.isEmpty())
    {
        for(QMap<QString, QString>::ConstIterator cit = attribute.begin();
            cit != attribute.end();
            ++cit)
        {
            m_outPutFile.write( (" " + cit.key() + "=\"" + cit.value() + "\"").toLocal8Bit() );
        }
    }

    m_outPutFile.write( (QString(">")).toLocal8Bit() );
//            writeElement
}

void TrackerForXmlFile::writtEndElement(const QString &element, bool newLine)
{
    if (newLine)
    {
        m_outPutFile.write("\n");
        m_outPutFile.write(m_indent.toLocal8Bit());
    }
    m_indent.remove(m_indent.length()-1, 1);

    m_outPutFile.write( ("</" + element + ">").toLocal8Bit() );

}

class TrackerForQDebug : public ITracker
{
public:
    virtual bool flush() { return true; }
    virtual void writeText(const QString & text);

protected:
    TrackerForQDebug(const QString & title);
    virtual ~TrackerForQDebug();

    //因为 writeBeginElement writtEndElement 的调用次数必须相同，防止外部调用次数不一致
    // 只允许 TrackElement TrackHelper 调用
    friend class TrackHelper;
    friend class TrackElement;
    virtual void writeBeginElement(const QString & element,
                           const QMap<QString, QString> & attribute = QMap<QString, QString>());
    virtual void writtEndElement(const QString & element, bool newLine = false);

protected:
    QString m_indent;
};



TrackerForQDebug::TrackerForQDebug(const QString &title)
    : ITracker(title),
      m_indent()
{
    QMap<QString, QString> attribute;
    attribute.insert("time", QDateTime::currentDateTime().toString());
    writeBeginElement(m_title, attribute);
}

TrackerForQDebug::~TrackerForQDebug()
{
    writtEndElement(m_title, true);
}

void TrackerForQDebug::writeText(const QString & text)
{
    QBuffer outBuf;
    outBuf.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
    outBuf.write(m_indent.toLocal8Bit());
    outBuf.putChar('\t');
    outBuf.write(text.toLocal8Bit());

    qDebug() << outBuf.data();
}

void TrackerForQDebug::writeBeginElement(const QString &element,
                                const QMap<QString, QString> & attribute)
{
    QBuffer outBuf;
    outBuf.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
    //outBuf.write("\n");
    m_indent.append('\t');
    outBuf.write(m_indent.toLocal8Bit());
    outBuf.write(("<" + element).toLocal8Bit());
    if (!attribute.isEmpty())
    {
        for(QMap<QString, QString>::ConstIterator cit = attribute.begin();
            cit != attribute.end();
            ++cit)
        {
            outBuf.write( (" " + cit.key() + "=\"" + cit.value() + "\"").toLocal8Bit() );
        }
    }

    outBuf.write( (QString(">")).toLocal8Bit() );

    qDebug() << outBuf.data();
}

void TrackerForQDebug::writtEndElement(const QString &element, bool newLine)
{
    QBuffer outBuf;
    outBuf.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
//    if (newLine)
//    {
//        m_outPutFile.write("\n");
//        m_outPutFile.write(m_indent.toLocal8Bit());
//    }
    outBuf.write(m_indent.toLocal8Bit());
    m_indent.remove(m_indent.length()-1, 1);

    outBuf.write( ("</" + element + ">").toLocal8Bit() );
    qDebug() << outBuf.data();
}

TrackHelper* TrackHelper::createXmlFileTracker(const QString &title, const QString &file, TrackHelper *pTrackHelper)
{
    if (pTrackHelper == NULL)
    {
        TrackHelper *t = new TrackHelper(new TrackerForXmlFile(title, file));
        return t;
    }
    else
    {
        pTrackHelper->appendTracker( new TrackerForXmlFile(title, file) );
        return pTrackHelper;
    }
}

TrackHelper* TrackHelper::createQDebugTracker(const QString & title,
                              TrackHelper *pTrackHelper)
{
    if (pTrackHelper == NULL)
    {
        TrackHelper *t = new TrackHelper(new TrackerForQDebug(title));
        return t;
    }
    else
    {
        pTrackHelper->appendTracker( new TrackerForQDebug(title) );
        return pTrackHelper;
    }
}

//void TrackHelper::deleteTrackHelper()
//{

//}

TrackHelper::TrackHelper(ITracker *pT, /*const QString &title,*/
                         bool funcP, bool debugP, bool warningP)
    :
      m_funcP(funcP),
      m_debugP(debugP),
      m_WarningP(warningP)
{
    assert(pT);

    s_trackHelperDeleter.trackHelperList.append(this);

    appendTracker(pT);
}

bool TrackHelper::appendTracker(ITracker *pT)
{
    assert(pT);

    if (!m_listTracker.contains(pT))
    {
        m_listTracker.append(pT);
        pT->increaseRef(pT);
    }

    return true;
}

void TrackHelper::removeTracker(ITracker *pT)
{
    if (pT)
    {
        if (m_listTracker.contains(pT))
        {
            m_listTracker.removeOne(pT);
            pT->decreaseRef(pT);
        }
    }
}

void TrackHelper::flush()
{
    foreach(ITracker *pTracker, m_listTracker)
    {
        pTracker->flush();
    }
}

ITracker* TrackHelper::getTracker(ETrackType trackType)
{
    switch (trackType) {
    case ETrackTypeXmlFile:
        foreach(ITracker *pTracker, m_listTracker)
        {
            TrackerForXmlFile* pT = dynamic_cast<TrackerForXmlFile*>(pTracker);
            if (pT)
                return pT;
        }
        break;
    case ETrackTypeQDebug:
        foreach(ITracker *pTracker, m_listTracker)
        {
            TrackerForQDebug* pT = dynamic_cast<TrackerForQDebug*>(pTracker);
            if (pT)
                return pT;
        }
        break;
    default:
        assert(!"error ETrackType");
        break;
    }

    return NULL;
}

TrackHelper::~TrackHelper()
{
    foreach(ITracker *pTracker, m_listTracker)
    {
        pTracker->flush();
        pTracker->decreaseRef(pTracker);
    }
}

void TrackHelper::setTrackEnable(bool funcEnable, bool debugEnable, bool warningEnable)
{
    m_funcP = (funcEnable);
    m_debugP = (debugEnable);
    m_WarningP = (warningEnable);
}

void TrackHelper::debug(const QString &text)
{
    TrackElement te(*this, TrackDebug);
    te.writeText(text);
}

void TrackHelper::warning(const QString &text)
{
    TrackElement te(*this, TrackWarning);
    te.writeText(text);
}

void TrackHelper::critical(const QString &text)
{
    TrackElement te(*this, TrackCritical);
    te.writeText(text);
}

void TrackHelper::writeText(TrackHelper::TrackEnum type, const QString &text)
{
    QString ele;
    if (checkPrint(type, ele))
    {
        foreach(ITracker *pTracker, m_listTracker)
        {
            pTracker->writeText(text);
        }
    }
}

void TrackHelper::trackBegin(TrackHelper::TrackEnum type, const QString &element,
                             const QMap<QString, QString> &attribute)
{
//    m_trackType = type;

    QString ele = element;
    if (checkPrint(type, ele))
    {
        foreach(ITracker *pTracker, m_listTracker)
        {
            pTracker->writeBeginElement(ele, attribute);
        }
    }

}

void TrackHelper::trackEnd(TrackHelper::TrackEnum type, const QString &element, bool newLine)
{
    QString ele = element;
    if (checkPrint(type, ele))
    {
        foreach(ITracker *pTracker, m_listTracker)
        {
            pTracker->writtEndElement(ele, newLine);
        }
    }
}

bool TrackHelper::checkPrint(TrackHelper::TrackEnum type, QString &element)
{
    if (type == TrackFunc)
    {
        if (m_funcP)
        {
            if (element.isEmpty())
                element = "func";
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (type == TrackDebug)
    {
        if (m_debugP)
        {
            element = "Debug";
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (type == TrackWarning )
    {
        if (m_WarningP)
        {
            element = "Warning";
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (type == TrackCritical)
    {
        element = "Critical";
        return true;
    }
    else
    {
        assert(0);
    }

    return true;
}

TrackHelper::TrackHelperDeleter::~TrackHelperDeleter()
{
    for(int i=0; i<trackHelperList.size(); i++)
    {
        delete trackHelperList.at(i);
    }
}

TrackHelper::TrackHelperDeleter TrackHelper::s_trackHelperDeleter;


//void TrackElement::debug(TrackHelper &t, const char *format, ...)
//{
//    va_list ap;
//    va_start(ap, format); // use variable arg list
//    qt_message(QtFatalMsg, msg, ap);
//    va_end(ap);
//    vsprintf
//}
