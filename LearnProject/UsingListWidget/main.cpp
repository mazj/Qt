#include "ListwidgetMainWnd.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ListwidgetMainWnd w;
    w.show();

    return a.exec();
}
