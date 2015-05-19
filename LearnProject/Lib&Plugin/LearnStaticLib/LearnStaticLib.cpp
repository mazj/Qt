#include "LearnStaticLib.h"
#include <QDebug>
#include "LearnStaticLibSub.h"


LearnStaticLib::LearnStaticLib()
{
    qDebug() << __FUNCTION__;
    LearnStaticLibSub lsls;
}
