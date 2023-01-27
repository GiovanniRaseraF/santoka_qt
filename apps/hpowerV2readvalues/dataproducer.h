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
#include <can_netlink.h>
#include <linux/can.h>
#include <unistd.h>
#include <vector>
#include <map>
#include <memory>

class canbus_thread : public QThread {
    Q_OBJECT

public:
    canbus_thread(QObject *parent = nullptr);
    ~canbus_thread();

    void run() override;
    void stop();

signals:
    void signalnewdata(struct can_frame newdata);

private:
    int cansocket = 0;
    struct sockaddr_can addr;

    bool stop_execution = false;
};

#endif // DATAPRODUCER_H
