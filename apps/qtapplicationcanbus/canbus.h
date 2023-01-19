#ifndef CANBUS_H
#define CANBUS_H

#include <QObject>
#include <memory>
#include <iostream>

#include <sys/socket.h>
#include <net/if.h>
#include <can_netlink.h>
#include <linux/can.h>
#include <unistd.h>
#include <vector>
#include <map>
#include <memory>


class canbus : public QObject
{
    Q_OBJECT
public:
    explicit canbus(QObject *parent = nullptr);

signals:
public slots:

private:
};

#endif // CANBUS_H
