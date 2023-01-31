#include "battery_filter.h"

battery_filter::battery_filter(std::shared_ptr<canbus_thread> canbus_producer, QObject *parent) : filter{canbus_producer, parent}
{
    on = {0x505, 0x506};
    name = "Battery Filter";

    connect(canbus_producer.get(), SIGNAL(signalnewdata(can_frame)), this, SLOT(receivednewframe(can_frame)));
}

void battery_filter::receivednewframe(const can_frame newframe){
    static uint8_t counter = 0;
    //if (canupdateinfo()){
        switch(newframe.can_id){
            case 0x505:

            emit new_bat_SOC();
            break;

            case 0x506:

            emit new_bat_BatteryTemperature(counter++ + 20 % 60);
            break;

            default:

            break;
        }
    //}

}

// TODO: implement it in a good way
bool battery_filter::canupdateinfo()
{
    return filter::canupdateinfo();
}
