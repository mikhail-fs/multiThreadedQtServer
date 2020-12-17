#include "mainwindow.h"
#include <QApplication>
#include "tcpclient.h"
#include <iostream>

int main(int argc, char *argv[])
{
    if(argc > 4)
    {
        std::cout << "Too many arguments" << std::endl;
        std::cout << "For example: address port -C:User:Password" << std::endl;
        return 0;
    }
    else if(argc < 4)
    {
        std::cout << "Too few arguments" << std::endl;
        std::cout << "For example: address port -C:User:Password" << std::endl;
        return 0;
    }
    else
    {
        QApplication a(argc, argv);
        //MainWindow w;

        TcpClient client(nullptr, argv);

        //w.show();

        return a.exec();
    }
}
