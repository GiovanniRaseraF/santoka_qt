#include "evbms_0x35A_filter.h"
#include "displayer/templatedconverter.h"
#include <QDebug>

evbms_0x35A::evbms_0x35A(std::shared_ptr<canbus_thread> canbus_producer, QObject *parent) : filter{canbus_producer, parent}
{
    on = {0x35A};
    name = "Evbms 0x35A: " + this->description.toStdString();

    // reserve data for data
    ev_WarningProtection.reserve(64);
    // init
    for(int i = 0; i < 64; i++) ev_WarningProtection.append(false);

    // connect
    connect(canbus_producer.get(), SIGNAL(signalnewdata(can_frame)), this, SLOT(receivednewframe(can_frame)));
}

void evbms_0x35A::receivednewframe(const can_frame newframe){
    uint8_t p1 = 0;

    switch(newframe.can_id){
        case 0x35A:
        for(int j = 0; j < 8; j++){
            p1 = filter::to_uint8(&newframe, j, j+1, 0, 1);
            for(int i = 0; i < 8; i++){
                uint8_t mask = 1 << i;
                bool active = (p1 & mask);

                // set
                ev_WarningProtection[(j*8)+i] = active;
            }
        }

        emit new_ev_WarningProtection(ev_WarningProtection);

        //qDebug() << "0x35A: " << __to_QString();
        break;

        default:
        break;
    }

    emit to_QString(__to_QString());
}

// TODO: implement it in a good way
bool evbms_0x35A::canupdateinfo()
{
    return filter::canupdateinfo();
}

QString evbms_0x35A::__to_QString()
{
    QString ret = "";
    for(int i = 0; i < ev_WarningProtection.size(); i++){
        bool a = ev_WarningProtection[i];
        if(a){
           ret += QString::number(1) + " ";
        }else{
           ret += QString::number(0) + " ";
        }
    }
    return ret;
}
