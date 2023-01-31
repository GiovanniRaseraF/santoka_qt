#include "filter.h"
#include <iostream>
#include <iomanip>
#include <cassert>

filter::filter(std::shared_ptr<canbus_thread> canbus_producer, QObject *parent) : QObject{parent}
{
    Q_UNUSED(canbus_producer);
    on = {};
    name = "generic filter";
    //connect(canbus_producer.get(), SIGNAL(signalnewdata(can_frame)), this, SLOT(newdatafromcan(can_frame)));
}

void filter::newdatafromcan(const can_frame newframe)
{
    std::cout << "Filter: ID:" << newframe.can_id << " - ";
    for(int i = 0; i < newframe.can_dlc; ++i){
        std::cout << std::hex << newframe.data[i] << " ";
    }
    std::cout << std::endl;
}

uint8_t filter::to_uint8(const can_frame *frame, uint8_t startbyte, uint8_t endbyte, uint8_t offset, uint8_t factor)
{
    Q_UNUSED(endbyte);
    assert(endbyte - startbyte == 1);
    return (uint8_t)((frame->data[startbyte] + offset) / factor);
}

uint16_t filter::to_uint16(const can_frame *frame, uint8_t startbyte, uint8_t endbyte, uint8_t offset, uint8_t factor)
{
    assert(endbyte - startbyte == 2);
    uint16_t ret = 0;
    ret |= ((uint16_t)frame->data[startbyte] << 8) | frame->data[startbyte+1];

    return (uint16_t)(ret + offset)*factor;
}


