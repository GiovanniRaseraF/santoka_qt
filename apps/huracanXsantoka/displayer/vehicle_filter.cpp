#include "vehicle_filter.h"
vehicle_filter::vehicle_filter(std::shared_ptr<canbus_thread> canbus_producer, QObject *parent) : filter{canbus_producer, parent}
{
    name = "Vehicle Filter";

    connect(canbus_producer.get(), SIGNAL(signalnewdata(can_frame)), this, SLOT(receivednewframe(can_frame)));
}

void vehicle_filter::receivednewframe(const can_frame newframe)
{
    switch(newframe.can_id){
        case 0x50C:
        vcl_status = filter::to_uint8(&newframe, 0, 1, 0, 1);
        vcl_mapInUse = filter::to_uint8(&newframe, 1, 2, 0, 1);
        vcl_inSeaWaterTemperature = filter::to_uint8(&newframe, 2, 3, 0, 1);
        vcl_outSeaWaterTemperature = filter::to_uint8(&newframe, 3, 4, 0, 1);
        vcl_inGlycoleTemperature = filter::to_uint8(&newframe, 4, 5, 0, 1);
        vcl_outGlycoleTemperature = filter::to_uint8(&newframe, 5, 6, 0, 1);

        emit new_vcl_status(vcl_status);
        emit new_vcl_mapInUse(vcl_mapInUse);
        emit new_vcl_inSeaWaterTemperature(vcl_inSeaWaterTemperature);
        emit new_vcl_outSeaWaterTemperature(vcl_outSeaWaterTemperature);
        emit new_vcl_inGlycoleTemperature(vcl_inGlycoleTemperature);
        emit new_vcl_outGlycoleTemperature(vcl_outGlycoleTemperature);
        break;

        case 0x50D:
        vcl_TotalHourCounter = filter::to_int32(&newframe, 0, 4, 0, 1);
        vcl_ElectricMotorHourCounter = filter::to_int32(&newframe, 4, 8, 0, 1);
        
        emit new_vcl_TotalHourCounter(vcl_TotalHourCounter);
        emit new_vcl_ElectricMotorHourCounter(vcl_ElectricMotorHourCounter);
        break;

        case 0x50E:    
        vcl_ThermicMotorHourCounter = filter::to_int32(&newframe, 0, 4, 0, 1);

        emit new_vcl_ThermicMotorHourCounter(vcl_ThermicMotorHourCounter);
        break;

        case 0x50F:    
        vcl_faults =filter::to_uint32(&newframe, 0, 4, 0, 1);
        vcl_warnings = filter::to_uint32(&newframe, 4, 8, 0, 1);

        emit new_vcl_faults(vcl_faults);
        emit new_vcl_warnings(vcl_warnings);
        break;

        default:
        break;
    }
}

bool vehicle_filter::canupdateinfo()
{
    return true;
}
