#ifndef TEMPLATEDCONVERTER_H
#define TEMPLATEDCONVERTER_H
#include <unistd.h>
#include <utility>
#include <QObject>

#ifndef SANTOKA
// NOT efficent, this runs a for every time
// to emprove this i can use MEMOIZATION
template<uint64_t s, uint64_t e>
uint64_t mask(){
    uint64_t ret = 0;

    for(uint64_t i = s; i < e; i++) {
       ret |= (0x8000000000000000 >> i);
    }

    return ret;
}

template<uint64_t sbyte, uint64_t ebyte>
uint64_t maskbyte(){
    uint64_t s = sbyte * 8, e = ebyte * 8;
    uint64_t ret = 0;

    for(uint64_t i = s; i < e; i++) {
       ret |= (0x8000000000000000 >> i);
    }

    return ret;
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
