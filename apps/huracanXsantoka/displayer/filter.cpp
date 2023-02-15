#include "filter.h"
#include <iostream>
#include <iomanip>
#include <cassert>
#include <utility>

filter::filter(std::shared_ptr<canbus_thread> canbus_producer, QObject *parent) : QObject{parent}
{
    Q_UNUSED(canbus_producer);
    on = {};
    name = "Generic filter";

    lastupdated = std::chrono::steady_clock::now();
}

uint64_t filter::convert(uint8_t *data, uint8_t len){
    uint64_t raw = 0;

    for(int i = len-1, j = 0; i >= 0; i--, j++){
       uint64_t di = data[j];
       raw |= di << (i*8);
    }

    return raw;
}

void filter::newdatafromcan(const can_frame newframe)
{
    std::cout << "Filter: ID:" << newframe.can_id << " - ";
    for(int i = 0; i < newframe.can_dlc; ++i){
        std::cout << std::hex << newframe.data[i] << " ";
    }
    std::cout << std::endl;
}

uint32_t filter::doconvert(uint64_t raw, std::size_t sb, std::size_t eb, uint8_t of, uint8_t f){
    int sbit = sb * 8, ebit = eb * 8, shiftright = 64 - ebit;

    uint64_t mask = 0;
    for(int i = sbit; i < ebit; i++){
        mask |= (0x8000000000000000) >> i;
    }

    uint64_t value = (raw & mask) >> shiftright;
    return (uint32_t) value;
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
    Q_UNUSED(frame);
    Q_UNUSED(offset);
    Q_UNUSED(factor);
    uint8_t bytes = endbyte - startbyte;
    Q_UNUSED(bytes);
    uint32_t ret = 0;

    return (float) ret;
}

std::string filter::to_string(const can_frame *frame, uint8_t startbyte, uint8_t endbyte, uint8_t offset, uint8_t factor)
{
    Q_UNUSED(frame);
    Q_UNUSED(offset);
    Q_UNUSED(factor);
    Q_UNUSED(startbyte);
    Q_UNUSED(endbyte);

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


