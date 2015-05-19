#include "qtablemainwnd.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTableMainWnd w;
    w.show();

    return a.exec();
}
