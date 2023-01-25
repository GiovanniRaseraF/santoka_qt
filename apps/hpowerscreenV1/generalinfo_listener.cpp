#include "generalinfo_listener.h"

generalinfo_listener::generalinfo_listener(QObject *parent):listener(parent){
    on = {0x500};
}

static uint8_t estract_uint8(const unsigned char *data, int len, int startbyte, int endbyte, int offset, float scale){
    return 0;
}

void generalinfo_listener::newcanvalue(const struct can_frame frame){
    if(isdataforme(frame)){
        info_BoatType = estract_uint8(frame.data, frame.can_dlc, 0, 1, 0, 1);
        info_ProtocolVersion = 0;
        info_ECUVersion = 0;
        info_DriveVersion = 0;
        info_ThermicEngineType = 0;
        info_ElectricMotorType = 0;
    }
}

