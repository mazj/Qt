#include "fullscreenmainwnd.h"
#include <QApplication>

/**
 * 这个例子 用来实验 全屏效果
 */


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FullScreenMainWnd w;
    w.show();

    return a.exec();
}
