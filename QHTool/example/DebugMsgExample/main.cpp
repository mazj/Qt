#include "DebugMsgMainWnd.h"
#include <QApplication>

//#define QH_D_MSG_FLG 0
//#define QH_D_MSG_FLG QH_D_MSG_CRITICAL_UP

#include "QHTool/qhDebugMsg.h"

TrackHelper *g_pTrackHelper = NULL;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qhInstallMsgHandler_file(QString("debugfile.txt"),
                             QString("DebugMsgExample"));

    const char * info = "info";
    QH_D() << "QH_D info";
    QH_DP( "QH_DP %s", info);
    QH_DP( "QH_DP info");

    QH_D_IF(1) << "QH_D_IF(1) info";
    QH_D_IF(0) << "QH_D_IF(0) info";
    QH_DP_IF(1, "QH_DP_IF info");
    QH_DP_IF(0, "QH_DP_IF info");
    QH_DP_IF(1, "QH_DP_IF %s", info);
    QH_DP_IF(0, "QH_DP_IF %s", info);

    QH_W() << "QH_W info";
    QH_WP( "QH_WP %s", info);
    QH_WP( "QH_WP info");

    QH_W_IF(1) << "QH_W_IF(1) info";
    QH_W_IF(0) << "QH_W_IF(0) info";
    QH_WP_IF(1, "QH_WP_IF info");
    QH_WP_IF(0, "QH_WP_IF info");
    QH_WP_IF(1, "QH_WP_IF %s", info);
    QH_WP_IF(0, "QH_WP_IF %s", info);

    QH_CRITICAL() << "QH_CRITICAL info";
    QH_CRITICALP( "QH_CRITICALP %s", info);
    QH_CRITICALP( "QH_CRITICALP info");

    QH_CRITICAL_IF(1) << "QH_CRITICAL_IF(1) info";
    QH_CRITICAL_IF(0) << "QH_CRITICAL_IF(0) info";
    QH_CRITICALP_IF(1, "QH_CRITICALP_IF info");
    QH_CRITICALP_IF(0, "QH_CRITICALP_IF info");
    QH_CRITICALP_IF(1, "QH_CRITICALP_IF %s", info);
    QH_CRITICALP_IF(0, "QH_CRITICALP_IF %s", info);

    // 下面的形式会出现错误
//    if (1)
//        QH_CRITICAL_IF(0) << "QH_CRITICALP_IF";
//    else
//        QH_D() << "should not out put!!";
    // 应该改成
    if (1) {
        QH_CRITICAL_IF(0) << "QH_CRITICALP_IF";
    }
    else
    {
        QH_D() << "should not out put!!";
    }

#ifndef QT_NO_DEBUG
//    QH_FATAL() << "QH_FATAL info";
    QH_FATALP( "QH_FATALP %s", info);
    QH_FATALP( "QH_FATALP info");

    QH_FATALP_IF(1, "QH_FATALP_IF(1) info");
    QH_FATALP_IF(0, "QH_FATALP_IF(1) info");

    // 下面两种形式不能 编译通过
//    QH_FATALP_IF(1, "QH_FATALP_IF(1) %s", info);
//    QH_FATALP_IF(0, "QH_FATALP_IF(1) %s", info);
    // 只能用 下面的形式
//    if(condition)
//        QH_FATALP( "QH_FATALP info");
#endif

    g_pTrackHelper = TrackHelper::createTracker("DebugMsgExample", "trackFile.xml");
    g_pTrackHelper->setTrackEnable(true, true, true);
//    g_pTrackHelper->setTrackEnable(false, false, false);
    QH_T_D(g_pTrackHelper, "begin");
    QH_T_FUNCL(g_pTrackHelper);
    QH_T_W(g_pTrackHelper, "QH_T_W");
    QH_T_C(g_pTrackHelper, "QH_T_C");

    QH_T_FLUSH(g_pTrackHelper);

    DebugMsgMainWnd w;
    w.show();

    return a.exec();
}
