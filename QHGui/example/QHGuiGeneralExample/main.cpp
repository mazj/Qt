#include "GeneralMainWnd.h"
#include <QApplication>
#include <QTextCodec>
#include <QTranslator>

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");
    QTextCodec* loc = QTextCodec::codecForLocale();
    QTextCodec:: setCodecForCStrings(loc);
    QTextCodec:: setCodecForLocale(loc);
    QTextCodec:: setCodecForTr(loc);

    QApplication a(argc, argv);
    QTranslator translator;
    if (translator.load("qt_zh_CN"))
    {
        QApplication::installTranslator(&translator);
    }

    GeneralMainWnd w;
    w.show();

    return a.exec();
}
