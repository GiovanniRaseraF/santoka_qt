#include "evbms_0x355_filter.h"
#include "displayer/templatedconverter.h"
#include <QDebug>

evbms_0x355::evbms_0x355(std::shared_ptr<canbus_thread> canbus_producer, QObject *parent) : filter{canbus_producer, parent}
{
    on = {0x355};
    name = "Evbms 0x355: " + this->description.toStdString();

    connect(canbus_producer.get(), SIGNAL(signalnewdata(can_frame)), this, SLOT(receivednewframe(can_frame)));
}

void evbms_0x355::receivednewframe(const can_frame newframe){
    uint64_t raw = filter::convert((uint8_t *)newframe.data, newframe.can_dlc);

    switch(newframe.can_id){
        case 0x355:
        ev_SOC = (uint16_t)filter::estract(raw, maskbyte<0, 2>(), 1, 0);
        qDebug() << (uint16_t)filter::estract(raw, maskbyte<0, 2>(), 2, 0);
        //ev_SOC = filter::doconvert(raw, 0, 2, 0, 10);
        ev_SOH = (uint16_t)filter::estract(raw, maskbyte<2, 4>(), 3, 0);
        ev_ResidualDischargeTime = (uint16_t)filter::estract(raw, maskbyte<4, 6>(), 5, 0);
        ev_Capacity= (uint16_t)filter::estract(raw, maskbyte<6, 8>(), 7, 0);

        emit new_ev_SOC(ev_SOC);
        emit new_ev_SOH(ev_SOH);
        emit new_ev_ResidualDischargeTime(ev_ResidualDischargeTime);
        emit new_ev_Capacity(ev_Capacity);

        qDebug() << "0x355: " << __to_QString();
        break;

        default:
        break;
    }

    emit to_QString(__to_QString());
}

// TODO: implement it in a good way
bool evbms_0x355::canupdateinfo()
{
    return filter::canupdateinfo();
}

QString evbms_0x355::__to_QString()
{
    QString ret = "";
    ret += "SOC:"   + QString::number(ev_SOC)   + "%\n";
    ret += "SOH:"   + QString::number(ev_SOH)   + "%\n";
    ret += "ResidualDischargeTime:"   + QString::number(ev_ResidualDischargeTime)   + "min\n";
    ret += "Capacity:"   + QString::number(ev_Capacity)   + "Ah\n";
    return ret;
}
