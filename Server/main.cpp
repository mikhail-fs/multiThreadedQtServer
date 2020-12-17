#include "mainwindow.h"
#include "tcpserver.h"
#include <QApplication>
#include <QLabel>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    if(argc != 2)
    {
        std::cout << "Incorrect count arguments" << std::endl;
        return 0;
    }

    w.setLabelPort(argv[1]);

    TcpServer server(nullptr, argv);

    QObject::connect(&server, &TcpServer::updateCountClients, &w, &MainWindow::setLabelCntClients);
    QObject::connect(&server, &TcpServer::sendParamsToMainForm, &w, &MainWindow::setParamsLabels);

    w.show();

    return a.exec();
}
