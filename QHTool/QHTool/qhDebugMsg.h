/**
  \file qhDebugMsg.h
  \brief debug ���ϵͳ
  ����������debug log ϵͳ��
    1.��װ qt�� debug ϵͳ
    2.�Լ��� xml logϵͳ��ʹ�� QH_T_MSG_FLG ����
  \author �ﺣ��
  \date 2014.2.24  ����
  */

#ifndef QHDEBUGMSG_H
#define QHDEBUGMSG_H

#include <QtCore/QDebug>
#include <QtCore/QNoDebug>
#include <QtCore/QFile>
#include <QtCore/QString>
#include <QtCore/QMap>
#include <QtCore/QList>

/** ************************************************************************
 * \name ��װ qt��debugϵͳ
 *  ʹ�� QH_D() QH_D_IF() QH_DP() QH_DP_IF() QH_W() QH_W_IF() QH_WP() QH_WP_IF()�Ⱥ���debug��
    ʹ�� �� QH_D_MSG_FLG ������ ����������Ƿ���Ч.
    ʹ�� qhInstallMsgHandler_file ������ض����ļ�
    ʹ����������


    #define QH_D_MSG_FLG QH_D_MSG_CRITICAL_UP // �����������
    #include "QHTool/qhDebugMsg.h"   // ����ͷ�ļ�
    func(){
    // �ض����ļ������п���
    qhInstallMsgHandler_file(QString("debugfile.txt"),
                             QString("DebugMsgExample"));

    // ʹ�ø�����������
    QH_D() << "QH_D info";
    QH_DP( "QH_DP %s", info);
    }
    ʹ��ʾ�� ��
    QHTool\\example\DebugMsgExample

    \note QH_D_IF QH_W_IF QH_CRITICAL_IF ��if else �ﾳ��ʹ���Ͽ��ܻ��и����ã���

    if (1)
        QH_D_IF(0) << "info";
    else
        doSomething();
    չ���� Ϊ
    if (1)
        if (condition) QH_D() << "info";
    else
        doSomething();
    �ĳ�
    if (1) {
        QH_D_IF(0) << "info";
    } else
        doSomething();
    ��û�и�������
 * @{
 */

/** ���������λ��ÿ������һ��λ
  */
#define QH_D_MSG_DEBUG_BIT (0x01)
#define QH_D_MSG_WARMING_BIT (0x02)
#define QH_D_MSG_CRITICAL_BIT (0x04)
#define QH_D_MSG_FATAL_BIT (0x08)

// ��ĳ�����������
#define QH_D_MSG_DEBUG_UP \
        (QH_D_MSG_DEBUG_BIT | QH_D_MSG_WARMING_BIT | QH_D_MSG_CRITICAL_BIT | QH_D_MSG_FATAL_BIT)
#define QH_D_MSG_ALL QH_D_MSG_DEBUG_UP
#define QH_D_MSG_WARMING_UP \
            (QH_D_MSG_WARMING_BIT | QH_D_MSG_CRITICAL_BIT | QH_D_MSG_FATAL_BIT)
#define QH_D_MSG_CRITICAL_UP (QH_D_MSG_CRITICAL_BIT | QH_D_MSG_FATAL_BIT)
#define QH_D_MSG_FATAL_UP QH_D_MSG_FATAL_BIT



/** Ĭ�϶���ӡ�����ƴ�ӡ�ĺ� ��
 * QH_D_MSG_FLG
  */
#ifndef QH_D_MSG_FLG
#define QH_D_MSG_FLG QH_D_MSG_ALL
#endif

#if  (QH_D_MSG_FLG & QH_D_MSG_DEBUG_BIT)
#define QH_D()   qDebug() << "[" << __FUNCTION__ << ":" << __LINE__ << "] "
#define QH_DP(...) \
    do { qDebug("[%s:%d]->", __FUNCTION__, __LINE__);\
        qDebug(__VA_ARGS__); } \
    while(0)
#else
inline QNoDebug QH_D() { return QNoDebug(); }
#define QH_DP(...) do{}while(0)
#endif

/** ����Ϊ��Ŵ�ӡ
  */
#define QH_D_IF(condition) if (condition) QH_D()
#define QH_DP_IF(condition, ...) do {if (condition) QH_DP(__VA_ARGS__); } while(0)

#if (QH_D_MSG_FLG & QH_D_MSG_WARMING_BIT)
#define QH_W()   qWarning() << "[" << __FUNCTION__ << ":" << __LINE__ << "] "
#define QH_WP(...) \
    do { qWarning("[%s:%d]->", __FUNCTION__, __LINE__);\
        qWarning(__VA_ARGS__); } \
    while(0)
#else
inline QNoDebug QH_W() { return QNoDebug(); }
#define QH_WP( ...) do{}while(0)
#endif

#define QH_W_IF(condition) if (condition) QH_W()
#define QH_WP_IF(condition, ...) do{ if (condition) QH_WP(__VA_ARGS__); } while(0)

#if (QH_D_MSG_FLG & QH_D_MSG_CRITICAL_BIT)
#define QH_CRITICAL()  qCritical() << "[" << __FUNCTION__ << ":" << __LINE__ << "] "
#define QH_CRITICALP(...) \
    do { qCritical("[%s:%d]->", __FUNCTION__, __LINE__);\
        qCritical(__VA_ARGS__); } while(0)
#else
inline QNoDebug QH_CRITICAL() { return QNoDebug(); }
#define QH_CRITICALP(...) do{}while(0)
#endif

#define QH_CRITICAL_IF(condition) if (condition) QH_CRITICAL()
#define QH_CRITICALP_IF(condition, ...) do{ if (condition) QH_CRITICALP(__VA_ARGS__); } while(0)

// ���� qFatal �Ƚ����⣬һ�����ֹ����ֻ�� QH_FATALP, û�� QH_FATAL()
#if (QH_D_MSG_FLG & QH_D_MSG_FATAL_BIT)
//#define QH_FATAL() qFatal()
#define QH_FATALP(constCharP, ...) \
    do { char buf[256] = "[%s:%d]->\n"; \
        strcat_s(buf, 256, constCharP); \
        qFatal(buf, __FUNCTION__, __LINE__, __VA_ARGS__); \
        } while(0)

#else
//inline QNoDebug QH_FATAL() { return QNoDebug(); }
#define QH_FATALP(...) do{}while(0)
#endif

#define QH_FATALP_IF(condition, ...) do{ if (condition) QH_FATALP(__VA_ARGS__); } while(0)


class QString;
class QComboBox;
class QTableWidgetItem;
class QTableWidget;

/**
 * ��װ qt �� MsgHandler ���ļ� file ��
 * @param file
 * @param softwareName
 * \test qInstallMsgHandler qInstallMessageHandler
 */
bool qhInstallMsgHandler_file(const QString & file, const QString & softwareName);

/** ***********************************************************************
 * @} ��װ qt��debugϵͳ
 */


/** *************************************************************************88
 * \name �Լ���xml��ʽ log׷��ϵͳ
 *���� log �� xml��ʽ�ļ��洢��
 * xml���ڷּ����룬�ǳ��ʺ���ʾ�������õĶ�ջ���̡�
 *
 * ���˼·��
 * �������࣬ һ�� ITracker ��Ӧһ���������������ж������͵ĸ�������
 *          ��� TrackHelper ��Ӧһ�� ITracker, �����Ҫʹ��  TrackHelper ����log��¼��
 *          һ�� TrackElement ��Ӧһ�� xml �ļ��Ľڵ�
 *
 * ʹ��ʾ����
 *  // ���ļ�Ϊ��λ ����log������𣬲�����Ĭ��ȫ��������ӱ��������� log
 *  #define QH_T_MSG_FLG (QH_T_MSG_WARMING_BIT|QH_T_MSG_CRITICAL_BIT)
    #include <QHTool/qhDebugMsg.h>

    main(){
        // ����һ�� ITracker����Ӧһ��xml�ļ������õ�һ��TrackHelper���Ժ��log��¼�ø�TrackHelper
        TrackHelper *pTrackHelper = TrackHelper::createXmlFileTracker("DebugMsgExample", "trackFile.xml");
        // �Ӻ����������� log����
        pTrackHelper->setTrackEnable(true, true, true);

        // ʹ�� ���������log��¼
        QH_T_FUNCL(pTrackHelper); //��¼�������ó�����Ϣ
        QH_T_D(pTrackHelper, "begin");
        QH_T_D_IF(condition, pTrackHelper, "begin");
        QH_T_W(pTrackHelper, "QH_T_W");
        QH_T_C(pTrackHelper, "QH_T_C");
        QH_T_FLUSH(pTrackHelper);  // ǿ��ˢ�����

        // �����ٴ��� TrackHelper��ʹ��ͬһ�� ITracker���������ͬһ�� xml �ļ���
        TrackHelper *p = new TrackHelper(pTrackHelper->getTracker());
        p->setTrackEnable(false, true, true);  //������������ͬ���Ӷ���ͬ�� TrackHelper �����log����ͬ ��
        QH_T_D_IF(1, p, "QH_T_D");
    }
    ʹ��ʾ�� ��
    QHTool\example\DebugMsgExample

 * @{
 */

class TrackHelper;
class TrackElement;
class ITracker;

enum ETrackType
{
    ETrackTypeXmlFile,
    ETrackTypeQDebug
};

/**
 * �����ֱ��ʹ�õ���
 */
class TrackHelper
{
public:
    enum TrackEnum
    {
        TrackFunc = 1,
        TrackDebug,
        TrackWarning,
        TrackCritical
    };

    /**
     * ���� һ�� XmlFileTracker TrackHelper�� һ�� Tracker ��Ӧһ�� xml��ʽ������ļ���һ��
     * ITracker �����ж�� TrackHelper��
     * @param title ����ļ��ĸ��ڵ�
     * @param file  �ļ�����
     * @return
     * \note ֻ������������� TrackHelper ����Ҫ�û��������١�
     */
    static TrackHelper *createXmlFileTracker(const QString & title,
                              const QString & file,  TrackHelper *pTrackHelper = NULL);

    static TrackHelper *createQDebugTracker(const QString & title,
                              TrackHelper *pTrackHelper = NULL);

//    static void deleteTrackHelper();

    TrackHelper(ITracker *pT, /*const QString & title,*/
                bool funcP = true, bool debugP = true, bool warningP = true);

    bool appendTracker(ITracker *pT);
    void removeTracker(ITracker *pT);
    /**
     * ǿ��ˢ�����
     */
    void flush();
    ITracker * getTracker(ETrackType trackType);

    /**
     * ���ø�����������log�Ƿ���Ч
     * @param funcEnable �����ĳ���ջ��Ϣ��Ч
     * @param debugEnable debug������Ϣ��Ч
     * @param warningEnable ���漶����Ϣ��Ч
     * \note û������ TrackCritical Σ�ռ������Ϣ�� Σ�ռ������Ϣ ��Զ��Ч
     */
    void setTrackEnable(bool funcEnable, bool debugEnable, bool warningEnable);
//    vois set

// �����ò�Ҫֱ��ʹ�� ����ĺ�����ʹ�� �� QH_T_D QH_T_W QH_T_C����
public:
    void debug(const QString &text);
    void warning(const QString &text);
    void critical(const QString &text);
//    static void warning(const char *format, ...);
//    static void critical(const char *format, ...);
protected:
    // ��ֹ����
    TrackHelper(const TrackHelper &);
    TrackHelper & operator =(const TrackHelper &);
    ~TrackHelper();

    friend class TrackElement;
    void trackBegin(TrackEnum type, const QString & element,
                        const QMap<QString, QString> & attribute = QMap<QString, QString>());
    void trackEnd(TrackEnum type, const QString & element, bool newLine = false);
    void writeText(TrackEnum type, const QString & text);

    bool checkPrint(TrackEnum type, QString & element);

protected:
    QList<ITracker*> m_listTracker;
    unsigned int m_funcP : 1;
    unsigned int m_debugP : 1;
    unsigned int m_WarningP : 1;
    unsigned int m_bDelAtExit : 1;
//    TrackEnum m_trackType;

    struct TrackHelperDeleter
    {
        QList<TrackHelper *> trackHelperList;
        ~TrackHelperDeleter();
    };
    static TrackHelperDeleter s_trackHelperDeleter;

};

/**
 * ��Ӧһ�� xml �ڵ㣬 �ڽ������� �����ڵ�Ŀ�ʼ��ǩ��writeText����ڵ����ݣ�
 * �������������ڵ�Ĺرձ�ǩ
 */
class TrackElement
{
public:
    TrackElement(TrackHelper & t,
                TrackHelper::TrackEnum type,                 
                 const QMap<QString, QString> & attribute,
                 const QString &element = QString(), bool newLine = false)
        :
          m_trackerHelper(t),
          m_trackType(type),
          m_element(element)
    {
        m_bNewLine = newLine;
        m_trackerHelper.trackBegin(m_trackType, m_element, attribute);
    }

    TrackElement(TrackHelper & t,
                 TrackHelper::TrackEnum type,
                 const QString &element = QString(), bool newLine = false)
        :
          m_trackerHelper(t),
          m_trackType(type),
          m_element(element)
    {
        m_bNewLine = newLine;
//        init(attribute);
        m_trackerHelper.trackBegin(m_trackType, m_element);
    }

    ~TrackElement()
    {
        m_trackerHelper.trackEnd(m_trackType, m_element, m_bNewLine);
    }

    void writeText( const QString & text) { m_trackerHelper.writeText(m_trackType, text); }

protected:
//    inline void init( const QMap<QString, QString> & attribute)
//    {
//        m_trackerHelper.getTracker().writeBeginElement(m_element, attribute);
//    }

protected:
    TrackHelper & m_trackerHelper;
    TrackHelper::TrackEnum m_trackType;
    QString m_element;
    bool m_bNewLine;
};

//log ��������λ
#define QH_T_MSG_DEBUG_BIT (0x010)      //debug ����
#define QH_T_MSG_WARMING_BIT (0x020)    //���漶��
#define QH_T_MSG_CRITICAL_BIT (0x040)   //Σ�ռ���
#define QH_T_MSG_FUNC_BIT (0x080)       //������ջ��ջ��Ϣ����

/** Ĭ�϶���ӡ�����ƴ�ӡ�ĺ� ��
 * QH_T_MSG_FLG
  */
#ifndef QH_T_MSG_FLG
#define QH_T_MSG_FLG (QH_T_MSG_FUNC_BIT|QH_T_MSG_DEBUG_BIT|QH_T_MSG_WARMING_BIT|QH_T_MSG_CRITICAL_BIT)
#endif

/** ǿ��ˢ�����
  */
#if (QH_T_MSG_FLG & (QH_T_MSG_FUNC_BIT|QH_T_MSG_DEBUG_BIT|QH_T_MSG_WARMING_BIT|QH_T_MSG_CRITICAL_BIT) )
#define QH_T_FLUSH(pTrackerHelper) pTrackerHelper->flush()
#else
#define QH_T_FLUSH(pTrackerHelper) ((void)0)
#endif

/**
  ���ٺ�����ջ��Ϣ�����
  �� ���ٺ�����ջ��Ϣ��Ч������������Ϣ�в���ʾ�������к���Ϣ��������ʾ
  */
#if (QH_T_MSG_FLG & QH_T_MSG_FUNC_BIT)

#define QH_T_FUNCL(pTrackerHelper) \
    TrackElement _trackElementTmp(*(pTrackerHelper), TrackHelper::TrackFunc, \
        QString(__FUNCTION__)+":"+QString::number(__LINE__), true)
#define QH_T_FUNCLI(pTrackerHelper, info) \
    QMap<QString, QString> attrs; \
    attrs["info"] = info; \
    TrackElement _trackElementTmp(*(pTrackerHelper), TrackHelper::TrackFunc, attrs, \
        QString(__FUNCTION__)+":"+QString::number(__LINE__), true)
#define QH_T_ADD_FUNC_LINE

#else
#define QH_T_FUNCL(trackerHelper) ((void)0)
#define QH_T_FUNCLI(pTrackerHelper, info)  ((void)0)
#define QH_T_ADD_FUNC_LINE ("["+QString(__FUNCTION__)+":"+QString::number(__LINE__)+"]")+
#endif

/** ����Ϊ������
  */
#define QH_T_FUNCL_IF(condition, pTrackerHelper) do{ if (condition) QH_T_FUNCL(pTrackerHelper); } while(0)

/** debug �����
  */
#if (QH_T_MSG_FLG&QH_T_MSG_DEBUG_BIT)
#define QH_T_D(trackerHelper, str) trackerHelper->debug(QH_T_ADD_FUNC_LINE str)
#else
#define QH_T_D(trackerHelper, str) ((void)0)
#endif

#define QH_T_D_IF(condition, trackerHelper, str) do{ if(condition) QH_T_D(trackerHelper, str); } while(0)

/** ���������
  */
#if (QH_T_MSG_FLG & QH_T_MSG_WARMING_BIT)
#define QH_T_W(trackerHelper, str) trackerHelper->warning(QH_T_ADD_FUNC_LINE str)
#else
#define QH_T_W(trackerHelper, str) ((void)0)
#endif

#define QH_T_W_IF(condition, trackerHelper, str) do{ if(condition) QH_T_W(trackerHelper, str); }while(0)


/** Σ�ռ��������
  */
#if (QH_T_MSG_FLG & QH_T_MSG_CRITICAL_BIT)
#define QH_T_C(trackerHelper, str) trackerHelper->critical(QH_T_ADD_FUNC_LINE str)
#else
#define QH_T_C(trackerHelper, str) ((void)0)
#endif

#define QH_T_C_IF(condition, trackerHelper, str) do { if(condition) QH_T_C(trackerHelper, str); } while(0)


/** *******************************************************************************
 * @}
 */

#ifdef COMPILE_QH_DEBUGMSG
#include "qhDebugMsg.cpp"
#endif

#endif // QHDEBUGMSG_H
