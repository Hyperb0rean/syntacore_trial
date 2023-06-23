#include "../include/utils.h"

uint32_t** blocks_partition(uint32_t start, uint32_t end, uint32_t threads) {
    uint32_t dn = (end - start + 1) / threads;
    uint32_t ** blocks = (uint32_t **)malloc(threads * sizeof(uint32_t *));
    for (uint32_t i = 0; i < threads; i++) {
        blocks[i] = (uint32_t *)malloc(2 * sizeof(uint32_t));
    }
    blocks[0][0] = start;
    blocks[0][1] = start + dn - 1;
    for (uint32_t i = 2; i < threads; i++) {
        blocks[i - 1][0] = start + dn * (i - 1);
        blocks[i - 1][1] = start + i * dn - 1;
    }
    blocks[threads - 1][0] = start + (threads - 1) * dn;
    blocks[threads - 1][1] = end;
    return blocks;
}