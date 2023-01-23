#include "battery_listener.h"

battery_listener::battery_listener(QObject *parent) : listener(parent)
{
     std::cout << ": battery listener" << std::endl;

     on = {0x500, 0x501};
}

void battery_listener::update(const can_frame frame){
    if(isdataforme(frame)){
        std::cout << "new battery frame" << std::endl;
    }
}
