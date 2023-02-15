#include "battery_filter.h"
#include "displayer/templatedconverter.h"

battery_filter::battery_filter(std::shared_ptr<canbus_thread> canbus_producer, QObject *parent) : filter{canbus_producer, parent}
{
    on = {0x505, 0x506};
    name = "Battery Filter";

    connect(canbus_producer.get(), SIGNAL(signalnewdata(can_frame)), this, SLOT(receivednewframe(can_frame)));
}

void battery_filter::receivednewframe(const can_frame newframe){
    uint64_t raw = filter::convert((uint8_t *)newframe.data, newframe.can_dlc);
    uint64_t m = mask<0, 16>();

    switch(newframe.can_id){
        case 0x505:
        bat_TotalVoltage = 				(float)filter::doconvert(raw, 0, 2, 0, 10) / 10;
        bat_TotalCurrent = 				(float)filter::doconvert(raw, 2, 4, 0, 10) / 10;
        bat_BatteryTemperature = 		filter::doconvert(raw, 4, 5, 0, 1);
        bat_BMSTemperature = 			filter::doconvert(raw, 5, 6, 0, 1);
        bat_SOC = 						filter::doconvert(raw, 6, 7, 0, 1);



        emit new_bat_TotalVoltage(bat_TotalVoltage);
        emit new_bat_TotalCurrent(bat_TotalCurrent);
        emit new_bat_BatteryTemperature(bat_BatteryTemperature);
        emit new_bat_BMSTemperature(bat_BMSTemperature);
        emit new_bat_SOC(bat_SOC);
        break;

        case 0x506:
        bat_faults = 		filter::to_uint8(&newframe, 0, 1, 0, 1);
        bat_warnings = 		filter::to_uint8(&newframe, 1, 2, 0, 1);
        bat_status = 		filter::to_uint8(&newframe, 2, 3, 0, 1);
        bat_Power = 					(float)filter::doconvert(raw, 3, 5, 0, 10) / 10;
        bat_TimeToEmpty = 				filter::doconvert(raw, 5, 7, 0, 1);
        bat_auxBatteryVoltage = 		(float)filter::doconvert(raw, 7, 8, 0, 10) / 10;
            
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

    emit to_QString(__to_QString());
}

// TODO: implement it in a good way
bool battery_filter::canupdateinfo()
{
    return filter::canupdateinfo();
}

QString battery_filter::__to_QString()
{
    QString ret = "";

    ret += "SOC: " + QString::number(bat_SOC) + " %\n";
    ret += "Voltage: " + QString::number(bat_TotalVoltage) + " V\n";
    ret += "Current: " + QString::number(bat_TotalCurrent) + " A\n";
    ret += "T Batt: " + QString::number(bat_BatteryTemperature) + " C\n";
    ret += "T BMS: " + QString::number(bat_BMSTemperature) + " C\n";
    ret += "F: " + QString::number(bat_faults) + " #\n";
    ret += "W: " + QString::number(bat_warnings) + " #\n";

    return ret;
}
