#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    WorkerThread *workerThread = new WorkerThread(this);
    connect(workerThread, &WorkerThread::resultReady, this, &MainWindow::handleResults);
    workerThread->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleResults(QString res){
    ui->pushButton->setText(res);
    ui->pushButton_2->setText(res);
}

