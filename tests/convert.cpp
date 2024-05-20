#include <iostream>
#include <stdint.h>

int main(){
    for(int16_t i = 0; i < INT16_MAX; i++) {
        float b = (float)((int16_t)i) / 10;
        std::cout << (int16_t)i << " -> " << b << std::endl;
    }

    return 0;
}