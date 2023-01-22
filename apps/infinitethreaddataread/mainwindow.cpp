#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QMatrix>
#include <QTransform>
#include <QPainter>
#include <QColor>
#include <QQuickView>
#include <QQuickWidget>
#include "cppgui.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Create the background thread to read canbus data
    backgroundCanbus = std::make_shared<WorkerThread>(this);
    backgroundCanbus->start();


    // Parse the filters
    battery = std::make_shared<listener>(this, backgroundCanbus);

    // Connect filtered data to ui element display
    connect(battery.get(), &listener::emitparsed, this, &MainWindow::handleResults);


    // Adding quick graphics

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleResults(int res){
    ui->battery->setText(QString::number(res));
}

void MainWindow::handlequickstring(QString res){
    qDebug() << res;
}
