#include "HealthManMainWnd.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	a.setQuitOnLastWindowClosed(false);	//���һ�����ڹر���Ҳ���˳�

    QTextCodec *pGbk = QTextCodec::codecForName("GBK");
    QTextCodec::setCodecForCStrings(pGbk);
    QTextCodec::setCodecForTr(pGbk);
    QTextCodec::setCodecForLocale(pGbk);

    Dialog w;
    w.show();
	w.raise();
	w.activateWindow();

    return a.exec();
}
