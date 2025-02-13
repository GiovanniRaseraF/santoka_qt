#include "evbms_0x358_filter.h"
#include "displayer/templatedconverter.h"
#include <QDebug>

evbms_0x358::evbms_0x358(std::shared_ptr<canbus_thread> canbus_producer, QObject *parent) : filter{canbus_producer, parent}
{
    on = {0x358};
    name = "Evbms 0x358: " + this->description.toStdString();

    connect(canbus_producer.get(), SIGNAL(signalnewdata(can_frame)), this, SLOT(receivednewframe(can_frame)));
}

void evbms_0x358::receivednewframe(const can_frame newframe){

    switch(newframe.can_id){
        case 0x358:
        ev_MaxCellVoltage = filter::to_uint16(&newframe, 0, 2, 0, 1) / 1000;
        ev_ModuleMaxVoltage = filter::to_uint8(&newframe, 2, 3, 0, 1);
        ev_CellMaxVoltage = filter::to_uint8(&newframe, 3, 4, 0, 1);
        ev_MinCellVoltage = filter::to_uint16(&newframe, 4, 6, 0, 1) / 1000;
        ev_ModuleMinVoltage = filter::to_uint8(&newframe, 6, 7, 0, 1);
        ev_CellMinVoltage = filter::to_uint8(&newframe, 7, 8, 0, 1);

        emit new_ev_MaxCellVoltage(ev_MaxCellVoltage);
        emit new_ev_ModuleMaxVoltage(ev_ModuleMaxVoltage);
        emit new_ev_CellMaxVoltage(ev_CellMaxVoltage);
        emit new_ev_MinCellVoltage(ev_MinCellVoltage);
        emit new_ev_ModuleMinVoltage(ev_ModuleMinVoltage);
        emit new_ev_CellMinVoltage(ev_CellMinVoltage);

        //qDebug() << "0x358: " << __to_QString();
        break;

        default:
        break;
    }

    emit to_QString(__to_QString());
}

// TODO: implement it in a good way
bool evbms_0x358::canupdateinfo()
{
    return filter::canupdateinfo();
}

QString evbms_0x358::__to_QString()
{
    QString ret = "";
    ret += "ev_MaxCellVoltage:"   + QString::number(ev_MaxCellVoltage)   + "%\n";
    ret += "ev_ModuleMaxVoltage:"   + QString::number(ev_ModuleMaxVoltage)   + "%\n";
    ret += "ev_CellMaxVoltage:"   + QString::number(ev_CellMaxVoltage)   + "%\n";
    ret += "ev_MinCellVoltage:"   + QString::number(ev_MinCellVoltage)   + "%\n";
    ret += "ev_ModuleMinVoltage:"   + QString::number(ev_ModuleMinVoltage)   + "%\n";
    ret += "ev_CellMinVoltage:"   + QString::number(ev_CellMinVoltage)   + "%\n";
    return ret;
}
