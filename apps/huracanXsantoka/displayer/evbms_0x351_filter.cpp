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

    int16_t bv = 0;
    switch(newframe.can_id){
        case 0x351:
        ev_CharginVoltageLimit =            ((float)(uint16_t)filter::estract(raw, maskbyte<0, 1>(), 1, 0)) * 0.1;

        emit new_ev_CharginVoltageLimit(ev_CharginVoltageLimit);
        qDebug() << "Received frame form 0x351\n" << __to_QString();
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
