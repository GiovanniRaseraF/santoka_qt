#include "evbms_0x356_filter.h"
#include "displayer/templatedconverter.h"
#include <QDebug>

evbms_0x356::evbms_0x356(std::shared_ptr<canbus_thread> canbus_producer, QObject *parent) : filter{canbus_producer, parent}
{
    on = {0x356};
    name = "Evbms 0x356: " + this->description.toStdString();

    connect(canbus_producer.get(), SIGNAL(signalnewdata(can_frame)), this, SLOT(receivednewframe(can_frame)));
}

void evbms_0x356::receivednewframe(const can_frame newframe){
    switch(newframe.can_id){
        case 0x356:
        ev_Voltage =       		(float)((((uint16_t)filter::to_uint8(&newframe, 1, 2, 0, 1)) << 8) | (filter::to_uint8(&newframe, 0, 1, 0, 1))) * 0.1;
        ev_Current=       		(float)((int16_t)(((filter::to_uint8(&newframe, 3, 4, 0, 1)) << 8) | (filter::to_uint8(&newframe, 2, 3, 0, 1)))) * 0.1;

        emit new_ev_Voltage(ev_Voltage);
        emit new_ev_Current(ev_Current);

        // Status emit
        if(ev_Current > 0){
            emit new_ev_Status(DISCHARGING);
        }else if(ev_Current == 0){
            emit new_ev_Status(STANDBY);
        }else{
            emit new_ev_Status(CHARGING);
        }

        //qDebug() << "0x356: " << __to_QString();
        break;

        default:
        break;
    }

    emit to_QString(__to_QString());
}

// TODO: implement it in a good way
bool evbms_0x356::canupdateinfo()
{
    return filter::canupdateinfo();
}

QString evbms_0x356::__to_QString()
{
    QString ret = "";
    ret += "Voltage:"   + QString::number(ev_Voltage)   + "%\n";
    ret += "Current:"   + QString::number(ev_Current)   + "%\n";
    return ret;
}
