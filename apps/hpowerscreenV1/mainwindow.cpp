#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    can_thread{std::make_shared<canbus_thread>(parent)}
{
    qRegisterMetaType<struct can_frame>();

    ui->setupUi(this);

    // connect can thread to data consumers

    // system log feature
    connect(can_thread.get(), SIGNAL(signalnewdata(struct can_frame)), this, SLOT(canbusdatalog(struct can_frame)));

    // start background thread
    can_thread->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}


// log
void MainWindow::canbusdatalog(struct can_frame frame){
    logstrign += QString::number(frame.can_id) + ": " + QString::number(frame.data[0]) + "\n";

    ui->tb_cablog->setText(logstrign);
}
