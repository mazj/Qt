#include "recursionmainwnd.h"
#include <QApplication>

/*
    递归的删除文件
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RecursionMainWnd w;
    w.show();

    return a.exec();
}
