#include "command_filter.h"

command_filter::command_filter(std::shared_ptr<canbus_thread> canbus_producer, QObject *parent)  : filter{canbus_producer, parent}
{
    name = "Command Filter";

    connect(canbus_producer.get(), SIGNAL(signalnewdata(can_frame)), this, SLOT(receivednewframe(can_frame)));
}

void command_filter::receivednewframe(const can_frame newframe)
{
    Q_UNUSED(newframe);
}

bool command_filter::canupdateinfo()
{
    return true;
}


