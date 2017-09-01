#include "testqssmainwnd.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TestQssMainWnd w;
    w.show();

    return a.exec();
}
