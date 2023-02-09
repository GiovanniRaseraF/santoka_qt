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
struct can_frame{
    uint32_t can_id;
    uint8_t can_dlc;
    uint8_t data[8];
};
#endif
#include <random>
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
#ifdef SANTOKA
    struct sockaddr_can addr;
#endif

    bool stop_execution = false;
};

// Fake can bus data creator
// Read from file and reproduce informations
class fake_canbus_thread : public canbus_thread{
public:
    fake_canbus_thread(std::string _filename, int _msleepval, QObject *parent = nullptr) : canbus_thread{parent}, filename{_filename}, msleepval{_msleepval}{
        std::cout << ": using fake canbus thread to generate data" << std::endl;
    }
    ~fake_canbus_thread(){
        stop_execution = true;
        QThread::msleep(10);
    };

private:
    std::string filename;
    std::ifstream file;

    int msleepval = 0;

    int rangemin = 0x490;
    int rangemax = 0x510;

public:
    virtual void run() override {
        std::random_device rd; // obtain a random number from hardware
        std::mt19937 gen(rd()); // seed the generator
        std::uniform_int_distribution<> distr(25, 63);

        int counter = 0;

        struct can_frame tosend;
        tosend.can_id = rangemin;
        tosend.can_dlc = 8;
        tosend.data[0] = 23;
        tosend.data[1] = 33;
        tosend.data[2] = 0;
        tosend.data[6] = 0;

        while(!stop_execution){
            tosend.can_id = rangemin + counter;
            counter = ((counter+1) % (rangemax - rangemin));

            for(int i = 0; i < tosend.can_dlc; i++){
                tosend.data[i] = (uint8_t) distr(gen);
            }
            emit signalnewdata(tosend);

           QThread::msleep(msleepval);
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
