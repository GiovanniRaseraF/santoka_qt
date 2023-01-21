#include "listener.h"
#include <iostream>
#include <QDebug>
#include <QString>

// Connecto to the producer at object creation
listener::listener(QObject *parent, std::shared_ptr<WorkerThread> bkworker)
    : QObject{parent}
{
    connect(bkworker.get(),  &WorkerThread::resultReady, this, &listener::parsedata);
}

// Example of a filter for data
// in this case performs mod operation to data
void listener::parsedata(int newvalue){
    qDebug() << QString::number(newvalue);

    emit emitparsed(newvalue % 10);
}
