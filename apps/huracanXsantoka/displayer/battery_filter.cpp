#include "battery_filter.h"
#include "displayer/templatedconverter.h"
#include <QDebug>

battery_filter::battery_filter(std::shared_ptr<canbus_thread> canbus_producer, QObject *parent) : filter{canbus_producer, parent}
{
    on = {0x505, 0x506};
    name = "Battery Filter";

    connect(canbus_producer.get(), SIGNAL(signalnewdata(can_frame)), this, SLOT(receivednewframe(can_frame)));
}

void battery_filter::receivednewframe(const can_frame newframe){
    uint64_t raw = filter::convert((uint8_t *)newframe.data, newframe.can_dlc);

    switch(newframe.can_id){
        case 0x505:
        bat_TotalVoltage = 				(float)filter::doconvert(raw, 0, 2, 0, 10) / 10;
        bat_TotalCurrent = 			    ((float)(int16_t)filter::doconvert(raw, 2, 4, 0, 10)) / 10;
        bat_BatteryTemperature = 		filter::estract(raw, maskbyte<4, 5>(), 5, 0);
        bat_BMSTemperature = 			filter::estract(raw, maskbyte<5, 6>(), 6, 0);
        bat_SOC = 						filter::estract(raw, maskbyte<6, 7>(), 7, 0);

        //qDebug() << bat_TotalCurrent << "   " << filter::doconvert(raw, 2, 4, 0, 10) << " " << (((uint64_t)raw & 0x0000ffff00000000) >> 32);

        emit new_bat_TotalVoltage(bat_TotalVoltage);
        emit new_bat_TotalCurrent(bat_TotalCurrent);
        emit new_bat_BatteryTemperature(bat_BatteryTemperature);
        emit new_bat_BMSTemperature(bat_BMSTemperature);
        emit new_bat_SOC(bat_SOC);
        break;

        case 0x506:
        // DOTO: fix battery power value on 32 bin arch
        bat_Power = 					(float)(int16_t)filter::estract(raw, maskbyte<3, 5>(), 5, 0) / 10;
        // DOTO: fix battery power value

        bat_TimeToEmpty = 				filter::estract(raw, maskbyte<5, 7>(), 7, 0);
        bat_auxBatteryVoltage = 		(float)filter::estract(raw, maskbyte<7, 8>(), 8, 0) / 10;
            
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

    ret += "SOC: " + 		QString::number(bat_SOC) + " %\n";
    ret += "Voltage: " + 	QString::number(bat_TotalVoltage) + " V\n";
    ret += "Current: " + 	QString::number(bat_TotalCurrent) + " A\n";
    ret += "Batt T: " + 	QString::number(bat_BatteryTemperature) + " C\n";
    ret += "BMS T: " + 		QString::number(bat_BMSTemperature) + " C\n";
    ret += "Power: " + 		QString::number(bat_Power) + " KW\n";
    ret += "TTE: " + 		QString::number(bat_TimeToEmpty) + " min\n";
    ret += "AuxVolt: " + QString::number(bat_auxBatteryVoltage) + " V\n";
    return ret;
}
