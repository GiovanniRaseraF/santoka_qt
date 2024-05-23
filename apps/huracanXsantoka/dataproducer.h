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
#ifdef SANTOKA
#include <can_netlink.h>
#include <linux/can.h>
#else
#include <linux/can.h>
#endif
#include <random>
#include <unistd.h>
#include <vector>
#include <map>
#include <memory>
#include <iostream>
#include <fstream>

#include "displayer/fakedata.h"

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
    struct sockaddr_can addr;

    bool stop_execution = false;
};

// Fake can bus data creator
// Read from file and reproduce informations
class fake_canbus_thread : public canbus_thread{
public:
    fake_canbus_thread(std::string _filename, int _msleepval, QObject *parent = nullptr) : filename{_filename}, msleepval{_msleepval}{
        Q_UNUSED(parent);
        std::cout << ": using fake canbus thread to generate data" << std::endl;
    }
    ~fake_canbus_thread(){
        stop_execution = true;
        QThread::msleep(msleepval);
    };

private:
    std::string filename;
    std::ifstream file;

    int msleepval = 0;

    int rangemin = 0x4FF;
    int rangemax = 0x520;

public:
    virtual void run() override {
        int offset = 0;
        std::random_device rd; // obtain a random number from hardware
        std::mt19937 gen(rd()); // seed the generator
        std::uniform_int_distribution<> distr(0, 255);

        struct can_frame tosend;
        tosend.can_id = rangemin;
        tosend.can_dlc = 8;

        while(!stop_execution){
            auto fdata = fakecandata[offset % fakecandata.size()];
            tosend.can_id = std::get<0>(fdata);

            tosend.data[0] = std::get<1>(fdata);
            tosend.data[1] = std::get<2>(fdata);
            tosend.data[2] = std::get<3>(fdata);
            tosend.data[3] = std::get<4>(fdata);
            tosend.data[4] = std::get<5>(fdata);
            tosend.data[5] = std::get<6>(fdata);
            tosend.data[6] = std::get<7>(fdata);
            tosend.data[7] = std::get<8>(fdata);

            emit signalnewdata(tosend);

            offset++;

           QThread::msleep(msleepval);
        }
    }

    std::string getinfo() override {
        std::string ret{};

        ret += filename;
        ret += "\n - sleep: " + std::to_string(msleepval) + " ms";

        return ret;
    }
};



#endif // DATAPRODUCER_H
