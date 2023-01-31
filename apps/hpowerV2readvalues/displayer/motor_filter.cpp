#include "motor_filter.h"
motor_filter::motor_filter(std::shared_ptr<canbus_thread> canbus_producer, QObject *parent)  : filter{canbus_producer, parent}
{
    name = "Motor Filter";

    connect(canbus_producer.get(), SIGNAL(signalnewdata(can_frame)), this, SLOT(receivednewframe(can_frame)));
}

void motor_filter::receivednewframe(const can_frame newframe)
{
    Q_UNUSED(newframe);
}

bool motor_filter::canupdateinfo()
{
    return true;
}
