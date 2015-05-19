#include "MainWidget.h"
#include "ui_MainWidget.h"
#include <QDebug>
#include <QDir>
#include <QPluginLoader>

int MainWidget::ms_num = 0;

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    // ������
    if (loadPlugin())
    {
        qDebug() << "load plugin successful";
    }
    else
    {
        qDebug() << "load plugin fail";
    }
}

MainWidget::~MainWidget()
{
    delete ui;
}

bool MainWidget::loadPlugin()
{
    QDir pluginDir(qApp->applicationDirPath());

    //�л������Ŀ¼
    if (pluginDir.cdUp() && pluginDir.cd("plugins"))
    {
        foreach(const QString& filename, pluginDir.entryList(QDir::Files))
        {
            // ���������
            QPluginLoader pluginLoader(pluginDir.absoluteFilePath(filename));

            //������
            QObject *p;
            if ( (p=pluginLoader.instance()) )
            {
                mpPlugin = qobject_cast<IMyPlugin*>(p);
                if (mpPlugin)
                    return true;
            }
        }
    }

    return false;
}

void MainWidget::on_pushButton_clicked()
{
    QString message = mpPlugin->echo(QString("text %1").arg(++ms_num));
    ui->label->setText(message);
}
