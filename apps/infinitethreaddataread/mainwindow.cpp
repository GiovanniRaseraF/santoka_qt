#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QMatrix>
#include <QTransform>
#include <QPainter>
#include <QColor>

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

void MainWindow::handleResults(int res){
    ui->battery->setText(QString::number(res));
    ui->speed->setText(QString::number(res % 100));
}

