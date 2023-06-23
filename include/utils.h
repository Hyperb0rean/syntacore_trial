//
// Created by hyperb0rean on 23.06.23.
//

#ifndef SYNTACORE_TRIAL_UTILS_H
#define SYNTACORE_TRIAL_UTILS_H

#include <inttypes.h>
#include <stdlib.h>

static inline uint32_t log2(const uint32_t x) {
    uint32_t y;
    asm ( "\tbsr %1, %0\n"
            : "=r"(y)
            : "r" (x)
            );
    return y;
}

static void strreverse(char* begin, char* end) {
    char aux;
    while(end>begin) aux=*end, *end--=*begin, *begin++=aux;
}

static int comp(const uint32_t * a, const uint32_t * b)
{
    return *b - *a;
}
static int compare (const void* a, const void* b)
{
    return comp((uint32_t *)a,(uint32_t *)b);
}

uint32_t ** blocks_partition(uint32_t start, uint32_t end, uint32_t threads);

#endif //SYNTACORE_TRIAL_UTILS_H
