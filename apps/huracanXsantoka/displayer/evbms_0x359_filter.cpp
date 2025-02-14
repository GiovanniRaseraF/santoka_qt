#include "evbms_0x359_filter.h"
#include "displayer/templatedconverter.h"
#include <QDebug>

evbms_0x359::evbms_0x359(std::shared_ptr<canbus_thread> canbus_producer, QObject *parent) : filter{canbus_producer, parent}
{
    on = {0x359};
    name = "Evbms 0x359: " + this->description.toStdString();

    connect(canbus_producer.get(), SIGNAL(signalnewdata(can_frame)), this, SLOT(receivednewframe(can_frame)));
}

void evbms_0x359::receivednewframe(const can_frame newframe){

    switch(newframe.can_id){
        case 0x359:
        ev_MaxTemperature = (int16_t)((((uint16_t)filter::to_uint8(&newframe, 1, 2, 0, 1)) << 8) | (filter::to_uint8(&newframe, 0, 1, 0, 1)));
        ev_ModuleMaxTemp = filter::to_uint8(&newframe, 2, 3, 0, 1);
        ev_CellMaxTemp = filter::to_uint8(&newframe, 3, 4, 0, 1);
        ev_MinTemperature = (int16_t)((((uint16_t)filter::to_uint8(&newframe, 5, 6, 0, 1)) << 8) | (filter::to_uint8(&newframe, 4, 5, 0, 1)));
        ev_ModuleMinTemp= filter::to_uint8(&newframe, 6, 7, 0, 1);
        ev_CellMinTemp= filter::to_uint8(&newframe, 7, 8, 0, 1);

        emit new_ev_MaxTemperature(ev_MaxTemperature);
        emit new_ev_ModuleMaxTemp(ev_ModuleMaxTemp);
        emit new_ev_CellMaxTemp(ev_CellMaxTemp);
        emit new_ev_MinTemperature(ev_MinTemperature);
        emit new_ev_ModuleMinTemp(ev_ModuleMinTemp);
        emit new_ev_CellMinTemp(ev_CellMinTemp);

        //qDebug() << "0x359: " << __to_QString();
        break;

        default:
        break;
    }

    emit to_QString(__to_QString());
}

// TODO: implement it in a good way
bool evbms_0x359::canupdateinfo()
{
    return filter::canupdateinfo();
}

QString evbms_0x359::__to_QString()
{
    QString ret = "";
    ret += "ev_MaxTemperature:"   + QString::number(ev_MaxTemperature)   + "%\n";
    ret += "ev_ModuleMaxTemp:"   + QString::number(ev_ModuleMaxTemp)   + "%\n";
    ret += "ev_CellMaxTemp:"   + QString::number(ev_CellMaxTemp)   + "%\n";
    ret += "ev_MinTemperature:"   + QString::number(ev_MinTemperature)   + "%\n";
    ret += "ev_ModuleMinTemp:"   + QString::number(ev_ModuleMinTemp)   + "%\n";
    ret += "ev_CellMinTemp:"   + QString::number(ev_CellMinTemp)   + "%\n";
    return ret;
}
