#include "dataproducer.h"
#include <QDebug>

canbus_thread::canbus_thread(QObject *parent) : QThread(parent){
    stop_execution = false;

    // Linux socket init
    //

    qDebug() << ": canbus thread RAII init\n";
}

void canbus_thread::run() {
    struct can_frame valuetoemit;
    valuetoemit.can_id = 0x100;
    valuetoemit.data[0] = 10;
    valuetoemit.data[1] = 2;
    valuetoemit.can_dlc = 2;

    // data recv from socket
    while(!stop_execution){
        emit signalnewdata(valuetoemit);

        QThread::sleep(1);
    }

    QThread::run();
}

void canbus_thread::stop(){
    stop_execution = true;
}



