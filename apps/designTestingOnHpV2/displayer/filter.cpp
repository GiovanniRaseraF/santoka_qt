#include "filter.h"
#include <iostream>
#include <iomanip>
#include <cassert>

filter::filter(std::shared_ptr<canbus_thread> canbus_producer, QObject *parent) : QObject{parent}
{
    Q_UNUSED(canbus_producer);
    on = {};
    name = "Generic filter";

    lastupdated = std::chrono::steady_clock::now();
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
    assert(endbyte - startbyte == 1);
    return (uint8_t)((frame->data[startbyte] + offset) / factor);
}

uint16_t filter::to_uint16(const can_frame *frame, uint8_t startbyte, uint8_t endbyte, uint8_t offset, uint8_t factor)
{
    assert(endbyte - startbyte == 2);
    uint16_t ret = 0;
    ret |= ((uint16_t)frame->data[startbyte] << 8) | frame->data[startbyte+1];

    return (uint16_t)(ret + offset)/factor;
}

uint32_t filter::to_uint32(const can_frame *frame, uint8_t startbyte, uint8_t endbyte, uint8_t offset, uint8_t factor)
{
    assert(endbyte - startbyte == 4);
    uint32_t ret = 0;
    ret |= ((uint32_t)frame->data[startbyte] << 24) |
            ((uint32_t)frame->data[startbyte+1] << 16) |
            ((uint32_t)frame->data[startbyte+2] << 8) |
            frame->data[startbyte+3];

    return (uint32_t)(ret + offset)/factor;
}

int8_t filter::to_int8(const can_frame *frame, uint8_t startbyte, uint8_t endbyte, uint8_t offset, uint8_t factor)
{
    assert(endbyte - startbyte == 1);
    return (int8_t)((frame->data[startbyte] + offset) / factor);
}

int16_t filter::to_int16(const can_frame *frame, uint8_t startbyte, uint8_t endbyte, uint8_t offset, uint8_t factor)
{
    assert(endbyte - startbyte == 2);
    int16_t ret = 0;
    ret |= ((int16_t)frame->data[startbyte] << 8) | frame->data[startbyte+1];

    return (int16_t)(ret + offset)/factor;
}

int32_t filter::to_int32(const can_frame *frame, uint8_t startbyte, uint8_t endbyte, uint8_t offset, uint8_t factor)
{
    assert(endbyte - startbyte == 4);
    int32_t ret = 0;
    ret |= ((int32_t)frame->data[startbyte] << 24) |
            ((int32_t)frame->data[startbyte+1] << 16) |
            ((int32_t)frame->data[startbyte+2] << 8) |
            frame->data[startbyte+3];

    return (int32_t)(ret + offset)/factor;
}

float filter::to_float(const can_frame *frame, uint8_t startbyte, uint8_t endbyte, uint8_t offset, uint8_t factor)
{
    uint8_t bytes = endbyte - startbyte;
    Q_UNUSED(bytes);
    uint32_t ret = 0;

    return (float) ret;
}

std::string filter::to_string(const can_frame *frame, uint8_t startbyte, uint8_t endbyte, uint8_t offset, uint8_t factor)
{
   return "TestVal";
}

bool filter::canupdateinfo()
{
    timenow = std::chrono::steady_clock::now();
    int counted = std::chrono::duration_cast<std::chrono::milliseconds>(timenow - lastupdated).count();

    if(counted > mininterval_millis){
        lastupdated = std::chrono::steady_clock::now();
        return true;
    }

    return false;
}


