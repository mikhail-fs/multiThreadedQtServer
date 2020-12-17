#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <unordered_map>
#include "thread.h"

class TcpServer : public QTcpServer
{
    Q_OBJECT

public:
    explicit TcpServer(QObject *parent = nullptr, char** argv = nullptr);

public slots:
    void receiveDisconnected(qintptr descriptor);
    void receiveConnected();
    void receiveParams(ThreadParams * params);

public:
    ThreadParams * m_threadParams;

signals:
    void updateCountClients(unsigned int count);
    void sendParamsToMainForm(ThreadParams * params);

private:
    std::unordered_map<qintptr, MyThread*> m_baseConnections;
    unsigned int m_port = 0;

protected:
    void incomingConnection(qintptr socketDescriptor);
};

#endif // TCPSERVER_H
