#ifndef TEMPLATEDCONVERTER_H
#define TEMPLATEDCONVERTER_H
#include <unistd.h>
#include <utility>
#include <QObject>

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

#endif // TEMPLATEDCONVERTER_H
