#include "FirstLevelMainWnd.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FirstLevelMainWnd w;
    w.show();

    return a.exec();
}
