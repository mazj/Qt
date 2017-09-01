#include "LocalCommunicator.h"

#include <QLocalServer>
#include <QLocalSocket>

LocalCommunicator::LocalCommunicator(QObject *parent) : QObject(parent)
{

}

LocalCommunicator::LocalCommunicator(const QString &communicatorName, QObject *parent)
: m_communicatorName(communicatorName)
, QObject(parent)
{
}

void LocalCommunicator::setCommunicatorName(const QString &communicatorName)
{
    m_communicatorName = communicatorName;
}

QString LocalCommunicator::getCommunicatorName() const
{
    return m_communicatorName;
}

bool LocalCommunicator::tryAsServerListen(const QString &communicatorName)
{
    m_communicatorName = communicatorName;
    return tryAsServerListen();
}

bool LocalCommunicator::tryAsServerListen()
{
    if(m_communicatorName.isEmpty())
    {
        qFatal() << "m_communicatorName is empty";
        return false;
    }

    QLocalServer *pServer = server();
    if(pServer->isListening())
        return true;

    if(isOtherRunning())
        return false;

    QLocalServer::removeServer(m_communicatorName);
    // 进行监听
    return pServer->listen(m_communicatorName);
}

bool LocalCommunicator::isOtherRunning()
{
    if(m_communicatorName.isEmpty())
    {
        qFatal() << "m_communicatorName is empty";
        return false;
    }

    if(server()->isListening())
        return false;

    // 用一个localsocket去连一下,如果能连上就说明
    // 有一个在运行了
    QLocalSocket ls;
    ls.connectToServer(m_communicatorName);
    if (ls.waitForConnected(1000)){
        // 说明已经在运行了
        ls.disconnectFromServer();
        ls.close();
        return true;
    }
    else
    {
        return false;
    }
}

QLocalServer *LocalCommunicator::server()
{
    if(!m_server)
    {
        m_server = new QLocalServer(this);
        connect(m_server, SIGNAL(newConnection()), this, SLOT(newConnection()));
    }

    return m_server;
}

QLocalSocket *LocalCommunicator::client()
{

}
