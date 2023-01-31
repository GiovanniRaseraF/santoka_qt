#include "generalinfo_filter.h"
generalinfo_filter::generalinfo_filter(std::shared_ptr<canbus_thread> canbus_producer, QObject *parent) : filter{canbus_producer, parent}
{
    name = "GeneralInfo Filter";

    connect(canbus_producer.get(), SIGNAL(signalnewdata(can_frame)), this, SLOT(receivednewframe(can_frame)));
}

void generalinfo_filter::receivednewframe(const can_frame newframe)
{
    Q_UNUSED(newframe);
}

bool generalinfo_filter::canupdateinfo()
{
    return true;
}
