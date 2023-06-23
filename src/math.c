#include "../include/math.h"

uint32_t gray_encode(uint32_t g)
{
    return g ^ (g >> 1);
}

uint32_t gray_decode(uint32_t gray)
{
    uint32_t bin;
    for (bin = 0; gray; gray >>= 1) {
        bin ^= gray;
    }
    return bin;
}

uint32_t weight(uint32_t int_num) {
    uint32_t count = 0;
    while (int_num) {
        if (int_num & 1) {
            count++;
        }
        int_num >>= 1;
    }
    return count;
}
