#include "motor_filter.h"
motor_filter::motor_filter(std::shared_ptr<canbus_thread> canbus_producer, QObject *parent)  : filter{canbus_producer, parent}
{
    name = "Motor Filter";

    connect(canbus_producer.get(), SIGNAL(signalnewdata(can_frame)), this, SLOT(receivednewframe(can_frame)));
}

void motor_filter::receivednewframe(const can_frame newframe)
{
   switch(newframe.can_id){
        case 0x500:
        drv_dcBusVoltage = filter::to_float(&newframe, 0, 2, 0, 10);
        drv_motorCurrent = filter::to_float(&newframe, 2, 4, 0, 10);
        drv_powerTemperature = filter::to_uint8(&newframe, 4, 5, 0, 1);
        drv_motorTemperature = filter::to_uint8(&newframe, 5, 6, 0, 1);
        drv_motorSpeed = filter::to_uint16(&newframe, 6, 8, 0, 1);
        
        emit new_drv_dcBusVoltage(drv_dcBusVoltage);
        emit new_drv_motorCurrent(drv_motorCurrent);
        emit new_drv_powerTemperature(drv_powerTemperature); 
        emit new_drv_motorTemperature(drv_motorTemperature); 
        emit new_drv_motorSpeed(drv_motorSpeed);

        break;
        case 0x502:
        drv_warnings = filter::to_uint32(&newframe, 0, 4, 0, 1);
        drv_faults = filter::to_uint32(&newframe, 4, 8, 0, 1);

        emit new_drv_warnings(drv_warnings);
        emit new_drv_faults(drv_faults); 
        break;

        case 0x503:
        drv_status = filter::to_uint8(&newframe, 0, 1, 0, 1);
        drv_referement = filter::to_uint16(&newframe, 1, 3, 0, 1);
        drv_currentLimit = filter::to_float(&newframe, 3, 5, 0, 10);
        drv_regenerationLimit = filter::to_float(&newframe, 5, 7, 0, 10);

        emit new_drv_status(drv_status);
        emit new_drv_referement(drv_referement);
        emit new_drv_currentLimit(drv_currentLimit); 
        emit new_drv_regenerationLimit(drv_regenerationLimit);
        break;

        default:
        break;
   }

   emit to_QString(__to_QString());
}

bool motor_filter::canupdateinfo()
{
    return true;
}

QString motor_filter::__to_QString()
{
    QString ret = "";

    ret +=
             ": " + QString::number(drv_dcBusVoltage) + " V\n"
            + ": " + QString::number(drv_motorCurrent) + " A\n"
            + ": " + QString::number(drv_motorVoltage) + " V\n"
            + ": " + QString::number(drv_motorSpeed) + " rpm\n"
            + ": " + QString::number(drv_referement) + " rpm\n"
            + ": " + QString::number(drv_currentLimit) + " A\n"
            + ": " + QString::number(drv_regenerationLimit) + " A\n"
            + ": " + QString::number(drv_powerTemperature) + " °C\n"
            + ": " + QString::number(drv_motorTemperature) + " °C\n"
            + ": " + QString::number(drv_status) + " bitfield\n"
            + ": " + QString::number(drv_warnings) + " bitfield\n"
            + ": " + QString::number(drv_faults) + " bitfield\n";
            
    return ret;
}
