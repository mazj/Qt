#include "LearnQmakeMainWindow.h"
#include <iostream>
#include <QApplication>

int main(int argc, char *argv[])
{
    std::cout << "hello" << std::endl;
    QApplication a(argc, argv);
    LearnQmakeMainWindow w;
    w.show();

    return a.exec();
}
