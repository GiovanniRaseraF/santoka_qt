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

const int BufferSize = 8192;
std::string buffer[BufferSize];

QWaitCondition bufferNotEmpty;
QWaitCondition bufferNotFull;
QMutex mutex;

int numUsedBytes = 0;

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

        std::cout << "can 0 setted " << std::endl;

        // Socket creation
        cansocket = socket(PF_CAN, SOCK_RAW, CAN_RAW);

        addr.can_family = AF_CAN;
        addr.can_ifindex = if_nametoindex("can0");

        int result = bind(cansocket, (struct sockaddr *)&addr, sizeof(addr));

        if (result == -1){
            std::cerr << "can bind error" << std::endl;
            return;
        }
    }

    void run() override
    {
        int nbytes = 0;
        struct can_frame frame;
        for (int i = 0;; ++i) {
            mutex.lock();
            if (numUsedBytes == BufferSize)
                bufferNotFull.wait(&mutex);

            nbytes = read(cansocket, &frame, sizeof(frame));
            std::string value = "" + std::to_string(frame.can_id) + "-";
            for(int y = 0; y < frame.can_dlc; y++){
                value += frame.data[y] + " ";
            }

            if(nbytes > 0){
                mutex.unlock();
                buffer[i % BufferSize] = value;
                mutex.lock();
            }

            ++numUsedBytes;
            bufferNotEmpty.wakeAll();
            mutex.unlock();

            QThread::sleep(1);
        }
    }
};

class Consumer : public QThread
{

public:
    Consumer(QObject *parent = NULL) : QThread(parent)
    {
    }

    void run() override
    {
        for (int i = 0;; ++i) {
            mutex.lock();
            if (numUsedBytes == 0)
                bufferNotEmpty.wait(&mutex);

            mutex.unlock();
            //fprintf(stderr, "%c ", buffer[i % BufferSize]);
            std::cout << buffer[i % BufferSize] <<  " ";
            mutex.lock();

            --numUsedBytes;
            bufferNotFull.wakeAll();
            mutex.unlock();
        }
        fprintf(stderr, "\n");
    }
};

#endif // CANREADER_H
