#include "dataproducer.h"
#include <QDebug>

#ifdef SANTOKA
canbus_thread::canbus_thread(QObject *parent) : QThread(parent){
    stop_execution = false;

    // Linux socket init
    system("sudo /sbin/ifconfig can0 down");
    system("sudo /sbin/canconfig can0 bitrate 250000");
    system("sudo /sbin/ip link set can0 type can bitrate 250000");
    system("sudo /sbin/ifconfig can0 up");

    qDebug() << ": can setup done\n";

    // socket
    cansocket = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    addr.can_family = AF_CAN;
    addr.can_ifindex = if_nametoindex("can0");

    // try binding
    int result = bind(cansocket, (struct sockaddr *)&addr, sizeof(addr));

    if (result == -1){
        qDebug() << ": can bind error\n";
        exit(1);
    }else{
        qDebug() << (": can0 binded, init reading process");
    }

    qDebug() << ": canbus thread RAII init\n";
}

canbus_thread::~canbus_thread(){
    stop();
    close(cansocket);
    system("sudo /sbin/ifconfig can0 down");

    QThread::msleep(20);
}

void canbus_thread::run() {
    int nbytes = 0;
    struct can_frame valuetoemit;

    // data recv from socket
    while(!stop_execution){
        // socket read
        nbytes = read(cansocket, &valuetoemit, sizeof(valuetoemit));

        if(nbytes > 0){
            emit signalnewdata(valuetoemit);
        }else{
            qDebug() << ": can_frame error, nbytes <= 0\n";
            QThread::msleep(200);
        }
    }

    QThread::run();
}

void canbus_thread::stop(){
    stop_execution = true;
}
#endif

// desktop
#ifdef DESKTOP
canbus_thread::canbus_thread(QObject *parent) : QThread(parent){
    stop_execution = false;

    // Linux socket init
    qDebug() << "You need to start canbus from your terminal !!";

    qDebug() << ": can setup done\n";

    // socket
    cansocket = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    addr.can_family = AF_CAN;
    addr.can_ifindex = if_nametoindex("can0");

    // try binding
    int result = bind(cansocket, (struct sockaddr *)&addr, sizeof(addr));

    if (result == -1){
        qDebug() << ": can bind error\n";
        exit(1);
    }else{
        qDebug() << (": can0 binded, init reading process");
    }
}

canbus_thread::~canbus_thread(){
    stop();
    close(cansocket);

    QThread::msleep(20);
}

void canbus_thread::run() {
    int nbytes = 0;
    struct can_frame valuetoemit;

    // data recv from socket
    while(!stop_execution){
        // socket read
        nbytes = read(cansocket, &valuetoemit, sizeof(valuetoemit));

        if(nbytes > 0){
            emit signalnewdata(valuetoemit);
        }else{
            qDebug() << ": can_frame error, nbytes <= 0\n";
            QThread::msleep(200);
        }
    }

    QThread::run();
}

void canbus_thread::stop(){
    stop_execution = true;
}
#endif

