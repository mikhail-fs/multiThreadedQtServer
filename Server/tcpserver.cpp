#include "tcpserver.h"
#include <iostream>

TcpServer::TcpServer(QObject *parent, char** argv) : QTcpServer(parent), m_port(std::atoi(argv[1]))
{
    if(!this->listen(QHostAddress::Any, m_port))
    {
        std::cout << "Server error!" << std::endl;
    }
    else
    {
        std::cout << "Server started!" << std::endl;
    }

    m_threadParams = new ThreadParams;
}

void TcpServer::incomingConnection(qintptr socketDescriptor)
{
    MyThread * thread = new MyThread(socketDescriptor, this);
    m_baseConnections[socketDescriptor] = thread;

    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(thread, &MyThread::sendDisconnected, this, &TcpServer::receiveDisconnected, Qt::DirectConnection);
    connect(thread, &MyThread::sendConnected, this, &TcpServer::receiveConnected, Qt::DirectConnection);
    connect(thread, &MyThread::sendParams, this, &TcpServer::receiveParams);

    thread->start();
}

void TcpServer::receiveConnected()
{
    emit updateCountClients(m_baseConnections.size());
}

void TcpServer::receiveDisconnected(qintptr descriptor)
{
    auto find = m_baseConnections.find(descriptor);
    if(find != m_baseConnections.end())
    {
        m_baseConnections.erase(find);
    }
    emit updateCountClients(m_baseConnections.size());
}

void TcpServer::receiveParams(ThreadParams * params)
{
    m_threadParams->m_countAuth += params->m_countAuth;
    m_threadParams->m_countDelete += params->m_countDelete;
    m_threadParams->m_countCreate += params->m_countCreate;

    emit sendParamsToMainForm(m_threadParams);
}
