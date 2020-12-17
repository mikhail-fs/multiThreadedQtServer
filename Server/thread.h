#ifndef THREAD_H
#define THREAD_H

#include <QThread>
#include <QTcpSocket>
#include <iostream>
#include <QSystemSemaphore>

struct ThreadParams{
    int m_countCreate = 0;
    int m_countAuth = 0;
    int m_countDelete = 0;
};

class MyThread : public QThread
{
    Q_OBJECT
public:
    ~MyThread();
    explicit MyThread(qintptr ID, QObject *parent = 0);
    void sendResponseAndCloseConn(QByteArray codeError);
    void run();

public slots:
    void receiveData();
    void disconnected();

signals:
    void error(QTcpSocket::SocketError socketerror);
    void sendDisconnected(qintptr descriptor);
    void sendConnected();
    void sendParams(ThreadParams * params);

private:
    QTcpSocket * m_connection;
    qintptr m_socketDescriptor;
    QSystemSemaphore * m_semaphore;
};

#endif // THREAD_H
