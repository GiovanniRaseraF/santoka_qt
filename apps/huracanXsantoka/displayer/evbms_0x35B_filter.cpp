#include "evbms_0x35B_filter.h"
#include "displayer/templatedconverter.h"
#include <QDebug>

evbms_0x35B::evbms_0x35B(std::shared_ptr<canbus_thread> canbus_producer, QObject *parent) : filter{canbus_producer, parent}
{
    on = {0x35B};
    name = "Evbms 0x35B: " + this->description.toStdString();

    // connect
    connect(canbus_producer.get(), SIGNAL(signalnewdata(can_frame)), this, SLOT(receivednewframe(can_frame)));
}

void evbms_0x35B::receivednewframe(const can_frame newframe){

    switch(newframe.can_id){
        case 0x35B:

        qDebug() << "0x35B: " << __to_QString();
        break;

        default:
        break;
    }

    emit to_QString(__to_QString());
}

// TODO: implement it in a good way
bool evbms_0x35B::canupdateinfo()
{
    return filter::canupdateinfo();
}

QString evbms_0x35B::__to_QString()
{
    QString ret = "";
    return ret;
}
