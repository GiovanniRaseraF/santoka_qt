#include "sniffer.h"
#include "displayer/templatedconverter.h"

sniffer_filter::sniffer_filter(std::shared_ptr<canbus_thread> canbus_producer, QObject *parent)  : filter{canbus_producer, parent}
{
    name = "Sniffer";

    connect(canbus_producer.get(), SIGNAL(signalnewdata(can_frame)), this, SLOT(receivednewframe(can_frame)));
}

void sniffer_filter::receivednewframe(const can_frame newframe)
{
    // generate string
    QString toSend = "";
    QString packetS = "";
    for(int i = 0; i < newframe.can_dlc; i++){
        int d = newframe.data[i];
        if(d < 0xF)
            packetS += QString("0%1 ").arg(d, 0, 16).toUpper();
        else
            packetS += QString("%1 ").arg(d, 0, 16).toUpper();
    }
    toSend += "can0 " + QString("0x%1").arg(newframe.can_id, 0,16) + " [" + QString("%1").arg(newframe.can_dlc) + "] " + packetS;

    // send the value
    emit new_canpacket(toSend);
}


bool sniffer_filter::canupdateinfo()
{
    return true;
}


