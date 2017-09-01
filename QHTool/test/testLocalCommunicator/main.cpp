#include "communicatormainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CommunicatorMainWindow w;
    w.show();

    return a.exec();
}
