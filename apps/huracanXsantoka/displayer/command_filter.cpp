#include "command_filter.h"
#include "displayer/templatedconverter.h"

command_filter::command_filter(std::shared_ptr<canbus_thread> canbus_producer, QObject *parent)  : filter{canbus_producer, parent}
{
    name = "Command Filter";

    connect(canbus_producer.get(), SIGNAL(signalnewdata(can_frame)), this, SLOT(receivednewframe(can_frame)));
}

void command_filter::receivednewframe(const can_frame newframe)
{
    uint64_t raw = filter::convert((uint8_t *)newframe.data, newframe.can_dlc);
    switch(newframe.can_id){
        case 0x50A:
        cmd_Throttle = 		filter::estract(raw, maskbyte<0, 1>(), 1, 0);
        cmd_gearRequested = filter::estract(raw, maskbyte<1, 2>(), 2, 0);
        cmd_gearValidated = filter::estract(raw, maskbyte<2, 3>(), 3, 0);
        cmd_TrimPosition = 	filter::estract(raw, maskbyte<3, 4>(), 4, 0);

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


