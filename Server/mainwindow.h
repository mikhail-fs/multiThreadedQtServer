#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "thread.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    ~MainWindow();
    void setLabelPort(const QString& port);
    explicit MainWindow(QWidget *parent = 0);

public slots:
    void setLabelCntClients(unsigned int count);
    void setParamsLabels(ThreadParams * params);

signals:


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
