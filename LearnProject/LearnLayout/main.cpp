#include "LayoutWidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LayoutWidget w;
    w.show();

    return a.exec();
}
