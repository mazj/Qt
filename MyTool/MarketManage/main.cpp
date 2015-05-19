#include <QApplication>
#include "marketmainwnd.h"
#include "userpassworddlg.h"
#include "global.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    UserPassWordDlg dlg;
    if (dlg.exec() != QDialog::Accepted)
    {
        return 0;
    }

    MarketMainWnd w;
    w.show();


    return a.exec();
}
