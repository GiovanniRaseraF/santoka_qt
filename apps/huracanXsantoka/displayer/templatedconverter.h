#ifndef TEMPLATEDCONVERTER_H
#define TEMPLATEDCONVERTER_H
#include <iostream>

template<std::size_t sb, std::size_t eb, uint8_t of, uint8_t f> struct conv{
uint32_t doconvert(uint64_t raw){
        constexpr uint8_t sbit = sb * 8, ebit = eb * 8, shiftright = 64 - ebit;
        std::cout << sbit << " " << ebit << " " << shiftright << " " << raw << std::endl;

        return 0;
    }
};

#endif // TEMPLATEDCONVERTER_H
