#include "EditedListMainWnd.h"
#include <QApplication>

#include <QTextCodec>

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");
    QTextCodec* loc = QTextCodec::codecForLocale();
    QTextCodec:: setCodecForCStrings(loc);
    QTextCodec:: setCodecForLocale(loc);
    QTextCodec:: setCodecForTr(loc);

    QApplication a(argc, argv);
    EditedListMainWnd w;
    w.show();

    return a.exec();
}
