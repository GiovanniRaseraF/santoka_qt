#include "battery_filter.h"

battery_filter::battery_filter(std::shared_ptr<canbus_thread> canbus_producer, QObject *parent) : filter{canbus_producer, parent}
{
    on = {0x505, 0x506};
    name = "Battery Filter";

    connect(canbus_producer.get(), SIGNAL(signalnewdata(can_frame)), this, SLOT(receivednewframe(can_frame)));
}

void battery_filter::receivednewframe(const can_frame newframe){
    //if (canupdateinfo()){
        switch(newframe.can_id){
            case 0x505:
            bat_TotalVoltage = filter::to_float(&newframe, 0, 2, 0, 10);
            bat_TotalCurrent = filter::to_float(&newframe, 2, 4, 0, 10);
            bat_BatteryTemperature = filter::to_uint8(&newframe, 4, 5, 0, 1);
            bat_BMSTemperature = filter::to_uint8(&newframe, 5, 6, 0, 1);
            bat_SOC = filter::to_uint8(&newframe, 6, 7, 0, 1);

            emit new_bat_TotalVoltage(bat_TotalVoltage);
            emit new_bat_TotalCurrent(bat_TotalCurrent);
            emit new_bat_BatteryTemperature(bat_BatteryTemperature);
            emit new_bat_BMSTemperature(bat_BMSTemperature);
            emit new_bat_SOC(bat_SOC);
            break;

            case 0x506:
            bat_faults = filter::to_uint8(&newframe, 0, 1, 0, 1);
            bat_warnings = filter::to_uint8(&newframe, 1, 2, 0, 1);
            bat_status = filter::to_uint8(&newframe, 2, 3, 0, 1);
            bat_Power = filter::to_float(&newframe, 3, 5, 0, 10);
            bat_TimeToEmpty = filter::to_uint16(&newframe, 5, 7, 0, 1);
            bat_auxBatteryVoltage = filter::to_uint8(&newframe, 7, 8, 0, 10);
            
            emit new_bat_faults(bat_faults);
            emit new_bat_warnings(bat_warnings);
            emit new_bat_status(bat_status);
            emit new_bat_Power(bat_Power);
            emit new_bat_TimeToEmpty(bat_TimeToEmpty);
            emit new_bat_auxBatteryVoltage(bat_auxBatteryVoltage);
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
