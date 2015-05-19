#include "MainWindow.h"
#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
#if 0
    QApplication a(argc, argv);

    QTranslator translator;
    QString path = QCoreApplication::applicationDirPath();
    //if( translator.load("LearnLinguist_de", path + "/../../LearnLinguist"))
    if ( translator.load("LearnLinguist_de", QString("D:/D/TianItDoc/Qt/LearnProject/LearnLinguist")) )
    {
        QApplication::installTranslator(&translator);
    }

    MainWindow w;
    w.show();

    return a.exec();
#else
    QTranslator translator;
    //QString path = QCoreApplication::applicationDirPath();
    //if( translator.load("LearnLinguist_de", path + "/../../LearnLinguist"))
    if ( translator.load("LearnLinguist_de", QString("D:/D/TianItDoc/Qt/LearnProject/LearnLinguist")) )
    {
        QCoreApplication::installTranslator(&translator);
    }
    QString s1 = QObject::tr("my tr 1");
    QString s = QObject::tr("my tr 1");
    QString s2 = QObject::tr("my tr 2");
#endif
}
