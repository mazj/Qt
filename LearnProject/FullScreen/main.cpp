#include "fullscreenmainwnd.h"
#include <QApplication>

/**
 * ������� ����ʵ�� ȫ��Ч��
 */


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FullScreenMainWnd w;
    w.show();

    return a.exec();
}
