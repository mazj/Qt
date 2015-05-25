/**
  \file qhDebugMsg.h
  \brief debug 输出系统
  这里有两套debug log 系统，
    1.封装 qt的 debug 系统
    2.自己的 xml log系统，使用 QH_T_MSG_FLG 控制
  \author 田海福
  \date 2014.2.24  创建
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
 * \name 封装 qt的debug系统
 *  使用 QH_D() QH_D_IF() QH_DP() QH_DP_IF() QH_W() QH_W_IF() QH_WP() QH_WP_IF()等宏来debug，
    使用 宏 QH_D_MSG_FLG 来控制 各输出级别是否有效.
    使用 qhInstallMsgHandler_file 把输出重定向到文件
    使用样例如下


    #define QH_D_MSG_FLG QH_D_MSG_CRITICAL_UP // 定义输出级别
    #include "QHTool/qhDebugMsg.h"   // 包含头文件
    func(){
    // 重定向到文件，可有可无
    qhInstallMsgHandler_file(QString("debugfile.txt"),
                             QString("DebugMsgExample"));

    // 使用各个宏进行输出
    QH_D() << "QH_D info";
    QH_DP( "QH_DP %s", info);
    }
    使用示例 见
    QHTool\\example\DebugMsgExample

    \note QH_D_IF QH_W_IF QH_CRITICAL_IF 在if else 语境中使用上可能会有副作用，如

    if (1)
        QH_D_IF(0) << "info";
    else
        doSomething();
    展开后 为
    if (1)
        if (condition) QH_D() << "info";
    else
        doSomething();
    改成
    if (1) {
        QH_D_IF(0) << "info";
    } else
        doSomething();
    就没有副作用了
 * @{
 */

/** 定义输出的位，每个级别一个位
  */
#define QH_D_MSG_DEBUG_BIT (0x01)
#define QH_D_MSG_WARMING_BIT (0x02)
#define QH_D_MSG_CRITICAL_BIT (0x04)
#define QH_D_MSG_FATAL_BIT (0x08)

// 在某个级别上输出
#define QH_D_MSG_DEBUG_UP \
        (QH_D_MSG_DEBUG_BIT | QH_D_MSG_WARMING_BIT | QH_D_MSG_CRITICAL_BIT | QH_D_MSG_FATAL_BIT)
#define QH_D_MSG_ALL QH_D_MSG_DEBUG_UP
#define QH_D_MSG_WARMING_UP \
            (QH_D_MSG_WARMING_BIT | QH_D_MSG_CRITICAL_BIT | QH_D_MSG_FATAL_BIT)
#define QH_D_MSG_CRITICAL_UP (QH_D_MSG_CRITICAL_BIT | QH_D_MSG_FATAL_BIT)
#define QH_D_MSG_FATAL_UP QH_D_MSG_FATAL_BIT



/** 默认都打印，控制打印的宏 用
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

/** 条件为真才打印
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

// 由于 qFatal 比较特殊，一般会终止程序，只有 QH_FATALP, 没有 QH_FATAL()
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
 * 安装 qt 的 MsgHandler 到文件 file 中
 * @param file
 * @param softwareName
 * \test qInstallMsgHandler qInstallMessageHandler
 */
bool qhInstallMsgHandler_file(const QString & file, const QString & softwareName);

/** ***********************************************************************
 * @} 封装 qt的debug系统
 */


/** *************************************************************************88
 * \name 自己的xml格式 log追踪系统
 *整个 log 以 xml格式文件存储。
 * xml由于分级整齐，非常适合显示函数调用的堆栈过程。
 *
 * 设计思路：
 * 有三个类， 一个 ITracker 对应一个跟踪器，可以有多种类型的跟踪器；
 *          多个 TrackHelper 对应一个 ITracker, 外界主要使用  TrackHelper 进行log记录。
 *          一个 TrackElement 对应一个 xml 文件的节点
 *
 * 使用示例：
 *  // 以文件为单位 定义log输出级别，不定义默认全部输出。从编译层面控制 log
 *  #define QH_T_MSG_FLG (QH_T_MSG_WARMING_BIT|QH_T_MSG_CRITICAL_BIT)
    #include <QHTool/qhDebugMsg.h>

    main(){
        // 创建一个 ITracker（对应一个xml文件），得到一个TrackHelper，以后的log记录用该TrackHelper
        TrackHelper *pTrackHelper = TrackHelper::createXmlFileTracker("DebugMsgExample", "trackFile.xml");
        // 从函数级别设置 log级别
        pTrackHelper->setTrackEnable(true, true, true);

        // 使用 各个宏进行log记录
        QH_T_FUNCL(pTrackHelper); //记录函数调用出入信息
        QH_T_D(pTrackHelper, "begin");
        QH_T_D_IF(condition, pTrackHelper, "begin");
        QH_T_W(pTrackHelper, "QH_T_W");
        QH_T_C(pTrackHelper, "QH_T_C");
        QH_T_FLUSH(pTrackHelper);  // 强制刷新输出

        // 可以再创建 TrackHelper，使用同一个 ITracker，即输出到同一个 xml 文件中
        TrackHelper *p = new TrackHelper(pTrackHelper->getTracker());
        p->setTrackEnable(false, true, true);  //定义的输出级别不同，从而不同的 TrackHelper 输出的log级别不同 。
        QH_T_D_IF(1, p, "QH_T_D");
    }
    使用示例 见
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
 * 供外界直接使用的类
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
     * 创建 一个 XmlFileTracker TrackHelper。 一个 Tracker 对应一个 xml格式的输出文件，一个
     * ITracker 可以有多个 TrackHelper。
     * @param title 输出文件的根节点
     * @param file  文件名称
     * @return
     * \note 只创建，创建完的 TrackHelper 不需要用户主动销毁。
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
     * 强制刷新输出
     */
    void flush();
    ITracker * getTracker(ETrackType trackType);

    /**
     * 设置各个输出级别的log是否有效
     * @param funcEnable 函数的出入栈信息有效
     * @param debugEnable debug级别信息有效
     * @param warningEnable 警告级别信息有效
     * \note 没有设置 TrackCritical 危险级别的信息， 危险级别的信息 永远有效
     */
    void setTrackEnable(bool funcEnable, bool debugEnable, bool warningEnable);
//    vois set

// 外界最好不要直接使用 下面的函数，使用 宏 QH_T_D QH_T_W QH_T_C代替
public:
    void debug(const QString &text);
    void warning(const QString &text);
    void critical(const QString &text);
//    static void warning(const char *format, ...);
//    static void critical(const char *format, ...);
protected:
    // 禁止复制
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
 * 对应一个 xml 节点， 在建构函数 创建节点的开始标签，writeText输出节点内容，
 * 析构函数创建节点的关闭标签
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

//log 级别的输出位
#define QH_T_MSG_DEBUG_BIT (0x010)      //debug 级别
#define QH_T_MSG_WARMING_BIT (0x020)    //警告级别
#define QH_T_MSG_CRITICAL_BIT (0x040)   //危险级别
#define QH_T_MSG_FUNC_BIT (0x080)       //函数入栈出栈信息级别

/** 默认都打印，控制打印的宏 用
 * QH_T_MSG_FLG
  */
#ifndef QH_T_MSG_FLG
#define QH_T_MSG_FLG (QH_T_MSG_FUNC_BIT|QH_T_MSG_DEBUG_BIT|QH_T_MSG_WARMING_BIT|QH_T_MSG_CRITICAL_BIT)
#endif

/** 强制刷新输出
  */
#if (QH_T_MSG_FLG & (QH_T_MSG_FUNC_BIT|QH_T_MSG_DEBUG_BIT|QH_T_MSG_WARMING_BIT|QH_T_MSG_CRITICAL_BIT) )
#define QH_T_FLUSH(pTrackerHelper) pTrackerHelper->flush()
#else
#define QH_T_FLUSH(pTrackerHelper) ((void)0)
#endif

/**
  跟踪函数堆栈信息输出宏
  若 跟踪函数堆栈信息有效，则在其他信息中不显示函数和行号信息，否则显示
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

/** 条件为真才输出
  */
#define QH_T_FUNCL_IF(condition, pTrackerHelper) do{ if (condition) QH_T_FUNCL(pTrackerHelper); } while(0)

/** debug 输出宏
  */
#if (QH_T_MSG_FLG&QH_T_MSG_DEBUG_BIT)
#define QH_T_D(trackerHelper, str) trackerHelper->debug(QH_T_ADD_FUNC_LINE str)
#else
#define QH_T_D(trackerHelper, str) ((void)0)
#endif

#define QH_T_D_IF(condition, trackerHelper, str) do{ if(condition) QH_T_D(trackerHelper, str); } while(0)

/** 警告输出宏
  */
#if (QH_T_MSG_FLG & QH_T_MSG_WARMING_BIT)
#define QH_T_W(trackerHelper, str) trackerHelper->warning(QH_T_ADD_FUNC_LINE str)
#else
#define QH_T_W(trackerHelper, str) ((void)0)
#endif

#define QH_T_W_IF(condition, trackerHelper, str) do{ if(condition) QH_T_W(trackerHelper, str); }while(0)


/** 危险级别输出宏
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
