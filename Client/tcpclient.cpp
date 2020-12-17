#include "tcpclient.h"
#include <iostream>
#include <QApplication>

TcpClient::TcpClient(QObject* parent, char** argv) : QObject(parent), m_argv(argv)
{
    m_client = new QTcpSocket(this);
    m_client->connectToHost(QString(argv[1]), std::atoi(argv[2]));

    connect(m_client, &QIODevice::readyRead, this, &TcpClient::receiveData);
}

void TcpClient::receiveData()
{
    QByteArray Data = m_client->readAll();

    qDebug() << Data;

    if(Data == "200")
    {
        if(m_argv[3] != nullptr)
        {
            m_client->write(m_argv[3]);
            m_client->flush();
            m_client->waitForBytesWritten(5000);
        }
    }
    if(Data == "201" || Data == "400" || Data == "401" || Data == "404" || Data == "403")
    {
        QApplication::exit();
    }
}

