#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <unistd.h>
#include <iostream>
#include <QDebug>
#include <string>
#include <cstdio>

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
    //std::string s = std::string(counter++);
    QString ss = QString::number(counter++);
    ui->pushButton->setText(ss);
}
