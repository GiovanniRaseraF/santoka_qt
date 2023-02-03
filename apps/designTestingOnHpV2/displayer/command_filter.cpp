#include "command_filter.h"

command_filter::command_filter(std::shared_ptr<canbus_thread> canbus_producer, QObject *parent)  : filter{canbus_producer, parent}
{
    name = "Command Filter";

    connect(canbus_producer.get(), SIGNAL(signalnewdata(can_frame)), this, SLOT(receivednewframe(can_frame)));
}

void command_filter::receivednewframe(const can_frame newframe)
{
    switch(newframe.can_id){
        case 0x50A:
        cmd_Throttle = filter::to_uint8(&newframe, 0, 1, 0, 1);
        cmd_gearRequested = filter::to_uint8(&newframe, 1, 2, 0, 1);
        cmd_gearValidated = filter::to_uint8(&newframe, 2, 3, 0, 1);
        cmd_TrimPosition = filter::to_uint8(&newframe, 3, 4, 0, 1);

        emit new_cmd_Throttle(cmd_Throttle);
        emit new_cmd_gearRequested(cmd_gearRequested);
        emit new_cmd_gearValidated(cmd_gearValidated);
        emit new_cmd_TrimPosition(cmd_TrimPosition);
        break;

        default:
        break;
    }
}

bool command_filter::canupdateinfo()
{
    return true;
}


