/*
 * Author: Giovanni Rasera
 * GitHub: www.github.com/GiovanniRaseraF
 */

/*
 * Description: Listener for canbus data, subclasses need
 * to implement data filters
 */
#ifndef LISTENER_H
#define LISTENER_H

#include <QObject>

#include <sys/socket.h>
#include <net/if.h>
#include <can_netlink.h>
#include <linux/can.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <algorithm>
#include <functional>
#include "dataproducer.h"
#include <ciso646>

class listener : public QObject
{
public:
    explicit listener(QObject *parent = nullptr) : QObject(parent), on{}, conversion_map{}{}

    // To emprove performance use just map
    virtual bool isdataforme(const struct can_frame& frame){
        return std::find(on.begin(), on.end(), frame.can_id) != on.end();
    }

public:
    // listen on basic filter, on stands for ON_CHANNEL
    std::vector<int> on;

    // the map connect the type of channel to the data conversion needed
    std::map<int, int> conversion_map;
};

// Example
class examplelisten : public listener {
    Q_OBJECT
public:
    examplelisten(QObject *parent = nullptr, std::shared_ptr<canbus_thread> producer = nullptr) : listener(parent){
        on = {0x100, 0x200};

        // data observer
        connect(producer.get(), SIGNAL(signalnewdata(can_frame)), this, SLOT(printtodebug(can_frame)));
    }

    virtual bool isdataforme(const can_frame &frame) override {
        // listen on every frame for debug
       return false and listener::isdataforme(frame);
    }

public slots:
    void printtodebug(struct can_frame frame){
        if(isdataforme(frame)){
            std::cout << std::hex << ": id: " << frame.can_id << "-";
            for(int i = 0; i < frame.can_dlc; i++){
                std::cout << " " << std::hex << frame.data[i];
            }
            std::cout << std::endl;
        }
    }
};

#endif // LISTENER_H
