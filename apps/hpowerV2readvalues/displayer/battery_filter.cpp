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
            bat_TotalVoltage = 0;//(float(int.from_bytes(data[0 : 2], byteorder="big", signed=True)) / 10.0)
            bat_TotalCurrent = 0;//(float(int.from_bytes(data[2 : 4], byteorder="big", signed=True)) / 10.0)
            bat_BatteryTemperature = filter::to_uint8(&newframe, 4, 5, 0, 1);//int.from_bytes(data[4 : 5], byteorder="big", signed=False)
            bat_BMSTemperature = filter::to_uint8(&newframe, 5, 6, 0, 1);//int.from_bytes(data[5 : 6], byteorder="big", signed=False)
            bat_SOC = filter::to_uint8(&newframe, 6, 7, 0, 1);//int.from_bytes(data[6 : 7], byteorder="big", signed=False)

            emit new_bat_SOC(bat_SOC);
            emit new_bat_BMSTemperature(bat_BMSTemperature);
            emit new_bat_BatteryTemperature(bat_BatteryTemperature);
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
