#include "thermicmotor_filter.h"

thermicmotor_filter::thermicmotor_filter(std::shared_ptr<canbus_thread> canbus_producer, QObject *parent) : filter{canbus_producer, parent}
{
    name = "Thermic Motor Filter";

    connect(canbus_producer.get(), SIGNAL(signalnewdata(can_frame)), this, SLOT(receivednewframe(can_frame)));
}

void thermicmotor_filter::receivednewframe(const can_frame newframe)
{
    Q_UNUSED(newframe);
}

bool thermicmotor_filter::canupdateinfo()
{
    return true;
}
