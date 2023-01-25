#include "battery_listener.h"

battery_listener::battery_listener(QObject *parent, std::shared_ptr<canbus_thread> producer) : listener(parent)
{
    connect(producer.get(), SIGNAL(signalnewdata(can_frame)), this, SLOT(update(can_frame)));

    std::cout << ": battery listener" << std::endl;
    on = {0x501, 0x502};
}

void battery_listener::update(const can_frame frame){
    if(isdataforme(frame)){
        std::cout << "battery frame on: " << frame.can_id << std::endl;
    }
}
