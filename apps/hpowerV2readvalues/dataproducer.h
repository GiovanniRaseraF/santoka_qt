/*
 * Author: Giovanni Rasera
 * GitHub: www.github.com/GiovanniRaseraF
 */

/*
 * Description: Canbus data producer
 * : the goal is to take this class as simple as possible,
 * : all processing will be done by filters
 */

#ifndef DATAPRODUCER_H
#define DATAPRODUCER_H

#include <QObject>
#include <QThread>
#include <QMutexLocker>
#include <QMutex>

#include <sys/socket.h>
#include <net/if.h>
#if linux
#include <can_netlink.h>
#include <linux/can.h>
#else
struct can_frame{
    uint32_t can_id;
    uint8_t can_dlc;
    uint8_t data[8];
};
#endif
#include <unistd.h>
#include <vector>
#include <map>
#include <memory>
#include <iostream>
#include <fstream>

class canbus_thread : public QThread {
    Q_OBJECT

public:
    canbus_thread(QObject *parent = nullptr);
    ~canbus_thread();

    virtual void run() override;
    virtual void stop();
    virtual std::string getinfo(){
        std::string ret{};

        ret += "canbus_thread:";
        ret += "\n - readfrom: can0";

        return ret;
    }

signals:
    void signalnewdata(struct can_frame newdata);

protected:
    int cansocket = 0;
 #if linux
    struct sockaddr_can addr;
#endif

    bool stop_execution = false;
};

// Fake can bus data creator
// Read from file and reproduce informations
class fake_canbus_thread : public canbus_thread{
public:
    fake_canbus_thread(std::string _filename, QObject *parent = nullptr) : canbus_thread{parent}, filename{_filename}{
        std::cout << ": using fake canbus thread to generate data" << std::endl;
    }
    ~fake_canbus_thread() = default;

private:
    std::string filename;
    std::ifstream file;

public:
    virtual void run() override {
        struct can_frame tosend;
        tosend.can_id = 0x505;
        tosend.can_dlc = 8;
        tosend.data[0] = 23;
        tosend.data[1] = 33;
        tosend.data[2] = 0;
        tosend.data[6] = 0;

        while(!stop_execution){
           tosend.data[6]++;

           emit signalnewdata(tosend);

           QThread::msleep(50);
        }
    }

    std::string getinfo() override {
        std::string ret{};

        ret += "fake_canbus_thread: ";
        ret += "\n - filename: " + filename;

        return ret;
    }
};

#endif // DATAPRODUCER_H
