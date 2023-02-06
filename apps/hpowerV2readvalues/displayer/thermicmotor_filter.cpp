#include "thermicmotor_filter.h"

thermicmotor_filter::thermicmotor_filter(std::shared_ptr<canbus_thread> canbus_producer, QObject *parent) : filter{canbus_producer, parent}
{
    name = "Thermic Motor Filter";

    connect(canbus_producer.get(), SIGNAL(signalnewdata(can_frame)), this, SLOT(receivednewframe(can_frame)));
}

void thermicmotor_filter::receivednewframe(const can_frame newframe)
{
    switch(newframe.can_id){
        case 0x508:
        dsl_engineSpeed = filter::to_uint16(&newframe, 0, 2, 0, 1);
        dsl_coolingTemperature = filter::to_int8(&newframe, 2, 3, 0, 1);
        dsl_batteryVoltage = filter::to_float(&newframe, 3, 5, 0, 10);
        dsl_Throttle = filter::to_uint8(&newframe, 5, 6, 0, 1);
        dsl_GlowPlugStatus = filter::to_uint8(&newframe, 6, 7, 0, 1);
        dsl_status = filter::to_uint8(&newframe, 7, 8, 0, 1);

        emit new_dsl_engineSpeed(dsl_engineSpeed);
        emit new_dsl_coolingTemperature(dsl_coolingTemperature);
        emit new_dsl_batteryVoltage(dsl_batteryVoltage);
        emit new_dsl_Throttle(dsl_Throttle);
        emit new_dsl_GlowPlugStatus(dsl_GlowPlugStatus);
        emit new_dsl_status(dsl_status);
        break;
        case 0x509:
        dsl_FuelLevel1 = filter::to_uint8(&newframe, 0, 1, 0, 1);
        dsl_FuelLevel2 = filter::to_uint8(&newframe, 1, 2, 0, 1);
        
        emit new_dsl_FuelLevel1(dsl_FuelLevel1);
        emit new_dsl_FuelLevel2(dsl_FuelLevel2);
        break;

        default:
        break;
    }
}

bool thermicmotor_filter::canupdateinfo()
{
    return true;
}
