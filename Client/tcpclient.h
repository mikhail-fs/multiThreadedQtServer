#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTcpSocket>

class TcpClient : public QObject
{
    Q_OBJECT
public:
    explicit TcpClient(QObject* parent = nullptr, char** argv = nullptr);

signals:

public slots:
    void receiveData();

private:
    QTcpSocket* m_client = nullptr;
    char** m_argv = nullptr;
};

#endif // TCPCLIENT_H
