#ifndef LOCALCOMMUNICATOR_H
#define LOCALCOMMUNICATOR_H

#include <QObject>
class QLocalServer;
class QLocalSocket;

class LocalCommunicator : public QObject
{
    Q_OBJECT
public:
    explicit LocalCommunicator(QObject *parent = 0);
    explicit LocalCommunicator(const QString& communicatorName, QObject *parent = 0);
    void setCommunicatorName(const QString& communicatorName);
    QString getCommunicatorName() const;

    bool tryAsServerListen(const QString &communicatorName);
    bool tryAsServerListen();

signals:

private slots:
    void newConnection();
    void readyRead();
    void socketConnected();

    void socketDisconnected();

    void socketError(QLocalSocket::LocalSocketError);

    void socketStateChanged(QLocalSocket::LocalSocketState);

private:
    bool isOtherRunning();
    QLocalServer* server();
    QLocalSocket *client();

private:
    QString m_communicatorName;
    QLocalServer *m_server;
    QLocalSocket *m_ls;
};



#endif // LOCALCOMMUNICATOR_H
