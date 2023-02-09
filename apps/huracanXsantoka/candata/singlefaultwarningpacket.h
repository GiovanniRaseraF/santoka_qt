#ifndef SINGLEFAULTWARNINGPACKET_H
#define SINGLEFAULTWARNINGPACKET_H

#include <QObject>
#include <QMap>
#include <QString>

#include <map>
#include <tuple>

#include "dataproducer.h"

class singlefaultwarningpacket : public QObject
{
    Q_OBJECT
public:
    explicit singlefaultwarningpacket(int _canchannel = 0, std::vector<int>&& _importantbits = {}, QObject *parent = nullptr);
    ~singlefaultwarningpacket() = default;

    void addproducer(std::shared_ptr<canbus_thread> canbus);

signals:
    void updatebit(int c, int b, bool active);

public slots:
    void newpacket(struct can_frame newframe);

public:
    int canchannel;
    std::vector<int> importantbits;
};

#endif // SINGLEFAULTWARNINGPACKET_H
