#include "canlistener.h"
#include <iostream>

void CanPrintAll::update(struct can_frame frame){
    std::cout << "ID: " << frame.can_id << " DATA:";
    for(int i = 0; i < frame.can_dlc; i++){
        uint8_t v = frame.data[i];
        std::cout << " " << v;
    }
    std::cout << std::endl;
}

CanPrintAll::CanPrintAll()
    : CanListener("printall", std::vector<int>{ALLCHANNELS})
{

}

