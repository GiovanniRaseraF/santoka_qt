#include "mainwindow.h"
#include "canreader.h"
#include <QApplication>
#include <QObject>
#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <QThread>
#include <QWaitCondition>
#include <QMutex>
#include <memory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Controller c;
    std::shared_ptr<shareddata> shared = std::make_shared<shareddata>(shareddata());
    Producer p{nullptr, shared};
    Consumer c{nullptr, shared};
    p.start();
    c.start();

    MainWindow w;

    w.show();
    return a.exec();
}
