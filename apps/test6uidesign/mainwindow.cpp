#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <unistd.h>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    // source /opt/guf/GUF-Yocto-jethro-11.0-r8139-0-sdk/environment-setup-imx6guf-guf-linux-gnueabi
    // scp test6uidesign fdsa@192.168.1.207:/home/fdsa/repos/santoka_qt
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    std::cout << "Hello" << std::endl;
}
