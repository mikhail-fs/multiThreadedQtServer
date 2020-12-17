#include "thread.h"
#include "shared_memory.h"

//Code of HTTP messages
//200	OK
//201	Created
//400	Bad Request
//401	Unauthorized
//404	Not found
//403	Forbidden

MyThread::MyThread(qintptr ID, QObject * parent) : QThread(parent)
{
    m_semaphore = new QSystemSemaphore("MySemaphore", 1);
    this->m_socketDescriptor = ID;
}

MyThread::~MyThread()
{
    emit sendDisconnected(m_socketDescriptor);
}

void MyThread::sendResponseAndCloseConn(QByteArray codeError)
{
    m_connection->write(codeError);
    m_connection->flush();
    m_connection->waitForBytesWritten(3000);
    m_connection->close();
}

void MyThread::run()
{
    m_connection = new QTcpSocket();

    if(!m_connection->setSocketDescriptor(m_socketDescriptor))
    {
        emit error(m_connection->error());
        return;
    }

    connect(m_connection, SIGNAL(readyRead()), this, SLOT(receiveData()), Qt::DirectConnection);
    connect(m_connection, SIGNAL(disconnected()), this, SLOT(disconnected()));

    m_connection->write("200");
    m_connection->flush();
    m_connection->waitForBytesWritten(3000);

    emit sendConnected();

    exec();
}

void MyThread::receiveData()
{
    QByteArray data = m_connection->readAll();
    QByteArray flag = data.left(3);

    if(flag == "-C:")
    {
        m_semaphore->acquire();
        if(globalSharedMemory.addRecord(data.toStdString()))
        {
            sendResponseAndCloseConn("201");
        }
        else
        {
            sendResponseAndCloseConn("403");
        }
        m_semaphore->release();

        ThreadParams * params = new ThreadParams;
        ++params->m_countCreate;
        emit sendParams(params);
    }
    else if(flag == "-D:")
    {
        m_semaphore->acquire();
        if(globalSharedMemory.delRecord(data.toStdString()))
        {
            sendResponseAndCloseConn("201");
        }
        else
        {
            sendResponseAndCloseConn("404");
        }
        m_semaphore->release();

        ThreadParams * params = new ThreadParams;
        ++params->m_countDelete;
        emit sendParams(params);
    }
    else if(flag == "-A:")
    {
        m_semaphore->acquire();
        if(globalSharedMemory.isRecord(data.toStdString()))
        {
            sendResponseAndCloseConn("201");
        }
        else
        {
            sendResponseAndCloseConn("401");
        }
        m_semaphore->release();

        ThreadParams * params = new ThreadParams;
        ++params->m_countAuth;
        emit sendParams(params);
    }
    else
    {
        sendResponseAndCloseConn("400");
        std::cout << "Invalid incoming parameters" << std::endl;
    }
}

void MyThread::disconnected()
{
    m_connection->deleteLater();
    exit(0);
}
