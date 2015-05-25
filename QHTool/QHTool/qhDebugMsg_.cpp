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
#define TRACKER "Tracker"

/**
 * 一个 Tracker 对应一个 输出文件
 */
class Tracker
{
public:
    static Tracker *create(const QString & title, const QString & file);
    static int increaseRef(Tracker *t);
    static int decreaseRef(Tracker * & t);

    bool flush() { return m_outPutFile.flush(); }
    void writeText(const QString & text) { m_outPutFile.write(text.toLocal8Bit()); }

protected:
    //  禁止复制
    Tracker(const Tracker &);
    Tracker & operator =(const Tracker &);

    Tracker(const QString & title, const QString & file);
    virtual ~Tracker();

    //因为 writeBeginElement writtEndElement 的调用次数必须相同，防止外部调用次数不一致
    // 只允许 TrackElement TrackHelper 调用
    friend class TrackHelper;
    friend class TrackElement;
    void writeBeginElement(const QString & element,
                           const QMap<QString, QString> & attribute = QMap<QString, QString>());
    void writtEndElement(const QString & element, bool newLine = false);

protected:
    QFile m_outPutFile;
    QString m_indent;
    QString m_title;
    int m_refCount;
};

Tracker::Tracker(const QString &title, const QString &file)
    :
      m_outPutFile(file),
      m_indent(),
      m_title(title),
      m_refCount(0)
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

Tracker *Tracker::create(const QString &title, const QString &file)
{
    return new Tracker(title, file);
}

int Tracker::increaseRef(Tracker *t)
{
    t->m_refCount++;
    return t->m_refCount;
}

int Tracker::decreaseRef(Tracker *&t)
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

Tracker::~Tracker()
{
    writtEndElement(m_title, true);
    m_outPutFile.write("\n");
    m_outPutFile.flush();
    m_outPutFile.close();
}

void Tracker::writeBeginElement(const QString &element,
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

void Tracker::writtEndElement(const QString &element, bool newLine)
{
    if (newLine)
    {
        m_outPutFile.write("\n");
        m_outPutFile.write(m_indent.toLocal8Bit());
    }
    m_indent.remove(m_indent.length()-1, 1);

    m_outPutFile.write( ("</" + element + ">").toLocal8Bit() );

}

TrackHelper::TrackHelperDeleter::~TrackHelperDeleter()
{
    for(int i=0; i<trackHelperList.size(); i++)
    {
        delete trackHelperList.at(i);
    }
}

TrackHelper::TrackHelperDeleter TrackHelper::s_trackHelperDeleter;


TrackHelper *TrackHelper::createTracker(const QString &title, const QString &file)
{
//    atexit( TrackHelper::deleteTrackHelper );
    TrackHelper *t = new TrackHelper(Tracker::create(title, file));
    return t;
}

//void TrackHelper::deleteTrackHelper()
//{

//}

TrackHelper::TrackHelper(Tracker *pT, /*const QString &title,*/
                         bool funcP, bool debugP, bool warningP)
    :
      m_pTracker(pT),
      m_funcP(funcP),
      m_debugP(debugP),
      m_WarningP(warningP)
{
    assert(m_pTracker);
    m_pTracker->increaseRef(m_pTracker);
    s_trackHelperDeleter.trackHelperList.append(this);

//    if (!title.isEmpty())
//    {

    //    }
}

void TrackHelper::flush()
{
    m_pTracker->flush();
}

TrackHelper::~TrackHelper()
{
    m_pTracker->flush();
    m_pTracker->decreaseRef(m_pTracker);
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
        m_pTracker->writeText(text);
    }
}

void TrackHelper::trackBegin(TrackHelper::TrackEnum type, const QString &element,
                             const QMap<QString, QString> &attribute)
{
//    m_trackType = type;

    QString ele = element;
    if (checkPrint(type, ele))
    {
        m_pTracker->writeBeginElement(ele, attribute);
    }

}

void TrackHelper::trackEnd(TrackHelper::TrackEnum type, const QString &element, bool newLine)
{
    QString ele = element;
    if (checkPrint(type, ele))
    {
        m_pTracker->writtEndElement(ele, newLine);
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


//void TrackElement::debug(TrackHelper &t, const char *format, ...)
//{
//    va_list ap;
//    va_start(ap, format); // use variable arg list
//    qt_message(QtFatalMsg, msg, ap);
//    va_end(ap);
//    vsprintf
//}
