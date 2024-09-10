#include "singlefaultwarningpacket.h"
#include <cmath>
#include <iomanip>
#include <QDebug>

singlefaultwarningpacket::singlefaultwarningpacket(int _canchannel, std::vector<int> &&_importantbits, QObject *parent) : QObject(parent),
                                                                                                                          importantbits{std::move(_importantbits)}
{
    canchannel = _canchannel;
}

void singlefaultwarningpacket::addproducer(std::shared_ptr<canbus_thread> canbus)
{
    connect(canbus.get(), SIGNAL(signalnewdata(can_frame)), this, SLOT(newpacket(can_frame)));
}

void singlefaultwarningpacket::newpacket(can_frame newframe)
{
    if (newframe.can_id != (uint32_t)canchannel)
        return;

    // update only interesting bits
    for (int bit : importantbits)
    {
        int position = (int)std::floor(bit / 8);
        int offset = bit % 8;

        uint8_t mask = 1 << (offset);
        bool isactive = newframe.data[position] & mask;

        qDebug() << "position: " << position << " offset: " << offset << " mask: " << (uint32_t)mask << " is: " << isactive << " \n";

        emit updatebit(canchannel, bit, isactive);
    }
}
