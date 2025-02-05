#include "evbms_0x351_filter.h"
#include "displayer/templatedconverter.h"
#include <QDebug>

evbms_0x351::evbms_0x351(std::shared_ptr<canbus_thread> canbus_producer, QObject *parent) : filter{canbus_producer, parent}
{
    on = {0x351};
    name = "Evbms 0x351: " + this->description.toStdString();

    connect(canbus_producer.get(), SIGNAL(signalnewdata(can_frame)), this, SLOT(receivednewframe(can_frame)));
}

void evbms_0x351::receivednewframe(const can_frame newframe){
    uint64_t raw = filter::convert((uint8_t *)newframe.data, newframe.can_dlc);

    switch(newframe.can_id){
        case 0x351:
        ev_CharginVoltageLimit =    (float)((((uint16_t)filter::to_uint8(&newframe, 1, 2, 0, 1)) << 8) | (filter::to_uint8(&newframe, 0, 1, 0, 1))) * 0.1;
        ev_CharginCurrentLimit =    (float)((((uint16_t)filter::to_uint8(&newframe, 3, 4, 0, 1)) << 8) | (filter::to_uint8(&newframe, 2, 3, 0, 1))) * 0.1;
        ev_DischargeCurrentLimit =  (float)((((uint16_t)filter::to_uint8(&newframe, 5, 6, 0, 1)) << 8) | (filter::to_uint8(&newframe, 4, 5, 0, 1))) * 0.1;
        ev_DischargeVoltageLimit =  (float)((((uint16_t)filter::to_uint8(&newframe, 7, 8, 0, 1)) << 8) | (filter::to_uint8(&newframe, 6, 7, 0, 1))) * 0.1;

        emit new_ev_CharginVoltageLimit(ev_CharginVoltageLimit);
        emit new_ev_CharginCurrentLimit(ev_CharginCurrentLimit);
        emit new_ev_DischargeCurrentLimit(ev_DischargeCurrentLimit);
        emit new_ev_DischargeVoltageLimit(ev_DischargeVoltageLimit);
        break;

        default:
        break;
    }

    emit to_QString(__to_QString());
}

// TODO: implement it in a good way
bool evbms_0x351::canupdateinfo()
{
    return filter::canupdateinfo();
}

QString evbms_0x351::__to_QString()
{
    QString ret = "";
    ret += "CharginVoltageLimit:"   + QString::number(ev_CharginVoltageLimit)   + "V\n";
    ret += "CharginCurrentLimit:"   + QString::number(ev_CharginCurrentLimit)   + "A\n";
    ret += "DischargeCurrentLimit:" + QString::number(ev_DischargeCurrentLimit) + "A\n";
    ret += "DischargeVoltageLimit:" + QString::number(ev_DischargeVoltageLimit) + "V\n";
    return ret;
}
