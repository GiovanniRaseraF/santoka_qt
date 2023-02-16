#include "generalinfo_filter.h"
#include "displayer/templatedconverter.h"

generalinfo_filter::generalinfo_filter(std::shared_ptr<canbus_thread> canbus_producer, QObject *parent) : filter{canbus_producer, parent}
{
    name = "GeneralInfo Filter";

    connect(canbus_producer.get(), SIGNAL(signalnewdata(can_frame)), this, SLOT(receivednewframe(can_frame)));
}

void generalinfo_filter::receivednewframe(const can_frame newframe)
{
    uint64_t raw = filter::convert((uint8_t *)newframe.data, newframe.can_dlc);

    switch(newframe.can_id){
        case 0x500:
        info_BoatType 			= filter::estract(raw, mask<0, 2>(), 1, 0); // add types
        info_ProtocolVersion 	= std::to_string((float)filter::estract(raw, maskbyte<1, 2>(), 2, 0) / 10);
        info_ECUVersion 		= std::to_string((float)filter::estract(raw, maskbyte<2, 4>(), 4, 0) / 100);
        info_DriveVersion 		= std::to_string((float)filter::estract(raw, maskbyte<4, 6>(), 6, 0) / 100);
        info_ThermicEngineType 	= filter::estract(raw, maskbyte<6, 7>(), 7, 0);
        info_ElectricMotorType 	= filter::estract(raw, maskbyte<7, 8>(), 8, 0);
        
        emit new_info_BoatType(info_BoatType);
        emit new_info_ProtocolVersion(info_ProtocolVersion);
        emit new_info_ECUVersion(info_ECUVersion);
        emit new_info_DriveVersion(info_DriveVersion);
        emit new_info_ThermicEngineType(info_ThermicEngineType);
        emit new_info_ElectricMotorType(info_ElectricMotorType);

        emit to_QString(__to_QString());
        break;

        default:
        break;
    }
}

bool generalinfo_filter::canupdateinfo()
{
    return true;
}

QString generalinfo_filter::__to_QString()
{
    QString ret = "";

    ret += "BoatType: \n  -" + (info_BoatType < tabboattype.size() ? tabboattype.at(info_BoatType):"NOT FOUND") + "\n"
        +  "PVersion: " + QString(info_ProtocolVersion.c_str()) + "\n"
        +  "ECUVerision: " + QString(info_ECUVersion.c_str()) + "\n"
        +  "DriveVersion: " + QString(info_DriveVersion.c_str()) + "\n"
        +  "ThermicType: " + (info_ThermicEngineType < tab1.size() ? tab1.at(info_ThermicEngineType) : "NOT FOUND") + "\n"
        +  "ElectricType: " + (info_ElectricMotorType < tab2.size() ? tab2.at(info_ElectricMotorType) : "NOT FOUND") +  "\n";

    return ret;
}
