#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setLabelCntClients(unsigned int count)
{
    ui->cntClients->setText("Count connected clients: " + QString::number(count));
}

void MainWindow::setLabelPort(const QString &port)
{
    ui->tcpPort->setText("Connected to port: " + port);
}

void MainWindow::setParamsLabels(ThreadParams * params)
{
    ui->countAuthReq->setText("Count authorization request: " + QString::number(params->m_countAuth));
    ui->countCrReq->setText("Count create request: " + QString::number(params->m_countCreate));
    ui->countDelReq->setText("Count delete request: " + QString::number(params->m_countDelete));
}
