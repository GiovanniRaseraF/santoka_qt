#include "battery_filter.h"

battery_filter::battery_filter(std::shared_ptr<canbus_thread> canbus_producer, QObject *parent) :
    QObject{parent}
{
    connect(canbus_producer.get(), SIGNAL(signalnewdata(can_frame)), this, SLOT(receivednewframe(can_frame)));
}

void battery_filter::receivednewframe(can_frame newframe){
    if(newframe.can_id == 0x505){
       bat_SOC++;
       bat_SOC %= 101;

       emit new_bat_SOC(bat_SOC);

    }else if(newframe.can_id == 0x506){
       bat_BatteryTemperature+=3;
       bat_BatteryTemperature %= 50;

       emit new_bat_BatteryTemperature(bat_BatteryTemperature);

    }
}
