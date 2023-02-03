#include "vahicle_filter.h"
vahicle_filter::vahicle_filter(std::shared_ptr<canbus_thread> canbus_producer, QObject *parent) : filter{canbus_producer, parent}
{
    name = "Vehicle Filter";

    connect(canbus_producer.get(), SIGNAL(signalnewdata(can_frame)), this, SLOT(receivednewframe(can_frame)));
}

void vahicle_filter::receivednewframe(const can_frame newframe)
{
    Q_UNUSED(newframe);
}

bool vahicle_filter::canupdateinfo()
{
    return true;
}
