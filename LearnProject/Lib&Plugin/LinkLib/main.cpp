#include <QCoreApplication>

#include "LearnSharedLib.h"
#include "LearnStaticLib.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    LearnSharedLib s;
    LearnStaticLib st;

    return a.exec();
}
