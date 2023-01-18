#ifndef CANREADER_H
#define CANREADER_H

#include <QApplication>
#include <QObject>
#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <QThread>
#include <QWaitCondition>
#include <QMutex>

#include <sys/socket.h>
#include <net/if.h>
#include <can_netlink.h>
#include <linux/can.h>
#include <unistd.h>
#include <vector>
#include <map>
#include <memory>

#include "canlistener.h"
class shareddata{
public:
    const int BufferSize = 8192;
    struct can_frame buffer[BufferSize];

    QWaitCondition bufferNotEmpty;
    QWaitCondition bufferNotFull;
    QMutex mutex;

    int numUsedBytes = 0;
};


class Producer : public QThread
{
public:
    int cansocket = 0;
    struct sockaddr_can addr;

    Producer(QObject *parent = NULL) : QThread(parent)
    {
        system("ifconfig can0 down");
        system("canconfig can0 bitrate 250000");
        system("ip link set can0 type can bitrate 250000");
        system("ifconfig can0 up");
        printf("canbus setup\n");

        // Socket creation
        cansocket = socket(PF_CAN, SOCK_RAW, CAN_RAW);
        addr.can_family = AF_CAN;
        addr.can_ifindex = if_nametoindex("can0");

        // try binding
        int result = bind(cansocket, (struct sockaddr *)&addr, sizeof(addr));

        if (result == -1){
            printf("can bind error\n");
        }else{
            printf("can0 binded, init reading process");
        }
    }

    void run() override
    {
        int nbytes = 0;
        struct can_frame frame;
        for (int i = 0;; ++i) {
            // read the frame
            nbytes = read(cansocket, &frame, sizeof(frame));

            // Comunication control
            mutex.lock();
            if (numUsedBytes == BufferSize)
                bufferNotFull.wait(&mutex);

            if(nbytes > 0){
                mutex.unlock();
                // save frame to be passed
                buffer[i % BufferSize] = frame;
                mutex.lock();
            }

            ++numUsedBytes;
            bufferNotEmpty.wakeAll();
            mutex.unlock();
        }
    }
};

class Consumer : public QThread
{
private:
    // TODO: use map to use direct call
    std::vector<std::shared_ptr<CanListener>> consumers;
public:
    Consumer(QObject *parent = NULL) : QThread(parent)
    {
        // Fake consumer
        consumers.push_back(std::make_shared<CanPrintAll>());
    }

    void run() override
    {
        for (int i = 0;; ++i) {
            mutex.lock();
            if (numUsedBytes == 0)
                bufferNotEmpty.wait(&mutex);

            mutex.unlock();
            struct can_frame newframe = buffer[i % BufferSize];
            consumers[0]->update(newframe);
            mutex.lock();

            --numUsedBytes;
            bufferNotFull.wakeAll();
            mutex.unlock();
        }
    }
};

#endif // CANREADER_H
