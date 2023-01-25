#include "generalinfo_listener.h"

generalinfo_listener::generalinfo_listener(QObject *parent, std::shared_ptr<canbus_thread> producer):listener(parent){
    // connect notification
    connect(producer.get(), SIGNAL(signalnewdata(can_frame)), this, SLOT(newcanvalue(can_frame)));

    on = {0x500};
}

static uint8_t estract_uint8(const unsigned char *data, int len, int startbyte, int endbyte, int offset, float scale){
    return 0;
}

void generalinfo_listener::newcanvalue(struct can_frame frame){
    if(isdataforme(frame)){
        info_BoatType = 2;//estract_uint8(frame.data, frame.can_dlc, 0, 1, 0, 1);
        info_ProtocolVersion = 1;
        info_ECUVersion = 2;
        info_DriveVersion = 2;
        info_ThermicEngineType = 3;
        info_ElectricMotorType = 4;

        // Emit values
        emit info_BoatType_signal(info_BoatType);
        emit info_ProtocolVersion_signal(info_ProtocolVersion);
        emit info_ECUVersion_signal(info_ECUVersion);
        emit info_DriveVersion_signal(info_DriveVersion);
        emit info_ThermicEngineType_signal(info_ThermicEngineType);
        emit info_ElectricMotorType_signal(info_ElectricMotorType);
    }
}

