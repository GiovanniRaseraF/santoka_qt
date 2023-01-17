#include "mainwindow.h"

#include <QApplication>
#include <QObject>
#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <QThread>
#include <QWaitCondition>
#include <QMutex>
#include "canreader.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Controller c;
    Producer p;
    Consumer c;
    p.start();
    c.start();

    MainWindow w;
    w.show();
    return a.exec();
}
