#include "DebugMsgMainWnd.h"
#include "ui_DebugMsgMainWnd.h"

//#define QH_T_MSG_FLG (QH_T_MSG_FUNC_BIT|QH_T_MSG_CRITICAL_BIT)
//#define QH_T_MSG_FLG (QH_T_MSG_WARMING_BIT|QH_T_MSG_CRITICAL_BIT)
#include <QHTool/qhDebugMsg.h>

extern TrackHelper *g_pTrackHelper;

DebugMsgMainWnd::DebugMsgMainWnd(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DebugMsgMainWnd)
{
    //     dumpObjectTree();
    //TrackHelper *p = new TrackHelper(g_pTrackHelper->getTracker(ETrackTypeXmlFile));
    TrackHelper *p = new TrackHelper(g_pTrackHelper->getTracker(ETrackTypeQDebug));
    p->appendTracker(g_pTrackHelper->getTracker(ETrackTypeXmlFile));
    QH_T_FUNCLI(p, "my info");
    QH_T_D_IF(1, p, "QH_T_D");
    QH_T_D_IF(0, p, "QH_T_D");
    QH_T_W_IF(1, p, "QH_T_W");
    QH_T_W_IF(0, p, "QH_T_W");
    QH_T_C_IF(1, p, "QH_T_C");
    QH_T_C_IF(0, p, "QH_T_C");

    ui->setupUi(this);
    subFunc();
}

DebugMsgMainWnd::~DebugMsgMainWnd()
{
    delete ui;
}

void DebugMsgMainWnd::subFunc()
{
    QH_T_FUNCL(g_pTrackHelper);
}
