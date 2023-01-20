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
    ui->pushButton->setText(QString::number(res));

    QTransform scale(0.1*res, 0, 0, 1.0, 0, 0);
    QTransform translate(1, 0, 0, 1, 50.0, 50.0);
    /*
    QTransform transform = scale * translate;
    QString filename = ":/hello.png";
    QPixmap p(filename);
    QColor color = QColor::Rgb;
    p = p.transformed(transform);
    QPixmap p9(":/hello.png");
        QPixmap temp(p9.size());
        temp.fill(Qt::transparent);
        QPainter pa(&temp);
        pa.setCompositionMode(QPainter::CompositionMode_Source);
        pa.drawPixmap(0, 0, p9);
        pa.setCompositionMode(QPainter::CompositionMode_DestinationIn);

        pa.end();
        p9 = temp;
    ui->label->setPixmap(p9);
*/
}

