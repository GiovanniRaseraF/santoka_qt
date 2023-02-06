#include "generalinfo_filter.h"
generalinfo_filter::generalinfo_filter(std::shared_ptr<canbus_thread> canbus_producer, QObject *parent) : filter{canbus_producer, parent}
{
    name = "GeneralInfo Filter";

    connect(canbus_producer.get(), SIGNAL(signalnewdata(can_frame)), this, SLOT(receivednewframe(can_frame)));
}

void generalinfo_filter::receivednewframe(const can_frame newframe)
{
     switch(newframe.can_id){
        case 0x500:
        info_BoatType 			= filter::to_uint8(&newframe, 0, 1, 0, 1);
        info_ProtocolVersion 	= filter::to_string(&newframe, 1, 2, 0, 10);
        info_ECUVersion 		= filter::to_string(&newframe, 2, 4, 0, 10);
        info_DriveVersion 		= filter::to_string(&newframe, 4, 6, 0, 10);
        info_ThermicEngineType 	= filter::to_uint8(&newframe, 6, 7, 0, 1);
        info_ElectricMotorType 	= filter::to_uint8(&newframe, 7, 8, 0, 1);
        
        emit new_info_BoatType(info_BoatType);
        emit new_info_ProtocolVersion(info_ProtocolVersion);
        emit new_info_ECUVersion(info_ECUVersion);
        emit new_info_DriveVersion(info_DriveVersion);
        emit new_info_ThermicEngineType(info_ThermicEngineType);
        emit new_info_ElectricMotorType(info_ElectricMotorType);
        break;

        default:
        break;
    }
}

bool generalinfo_filter::canupdateinfo()
{
    return true;
}
