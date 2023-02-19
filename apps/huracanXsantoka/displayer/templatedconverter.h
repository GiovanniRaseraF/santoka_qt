#ifndef TEMPLATEDCONVERTER_H
#define TEMPLATEDCONVERTER_H
#include <unistd.h>
#include <utility>
#include <QObject>

#ifdef SANTOKA
template<uint8_t s, uint8_t e, bool active, unsigned long  acc, uint8_t counter, bool start>
struct maskbits{};

template<uint8_t s, uint8_t e, bool active, unsigned long acc, uint8_t c>
struct maskbits<s, e, active, acc, c, false>
    : public maskbits<
        s,
        e,
        (c >= s && c < e),
        (((unsigned long)(c >= s && c < e)) << c) | acc,
        c+1,
        false
    >{};

template<uint8_t s, uint8_t e, bool active, unsigned long acc>
struct maskbits<s, e, active, acc, 64, false>{
    static const unsigned long value = acc;
};

template<uint8_t s, uint8_t e>
struct mask_base{
    static const unsigned long value = maskbits<64-e, 64-s, 0, 0, 0, false>::value;
};

template<uint64_t s, uint64_t e>
uint64_t mask(){
    return mask_base<s, e>::value;
}

template<uint64_t sbyte, uint64_t ebyte>
uint64_t maskbyte(){
    return mask_base<sbyte*8, ebyte*8>::value;
}
#else
// this is the better version because the filter is calculated at compile time
template<uint64_t s, uint64_t e, uint64_t c>
uint64_t mask(){
    if constexpr(c >= s && c < e)
        return (0x8000000000000000 >> c) | mask<s, e, c+1>();
    else if constexpr(c == 64)
        return 0;
    else
        return 0 | mask<s, e, c+1>();
}

template<uint64_t s, uint64_t e>
uint64_t mask(){
    if constexpr(s < 0 || e > 64 || s > e)
        return 0;
    else
        return mask<s, e, 0>();
}

template<uint64_t sbyte, uint64_t ebyte>
uint64_t maskbyte(){
    return mask<sbyte * 8, ebyte * 8>();
}
#endif
#endif // TEMPLATEDCONVERTER_H
