#include <string.h>
#include "../include/math.h"

void strreverse(char* begin, char* end) {

    char aux;

    while(end>begin)

        aux=*end, *end--=*begin, *begin++=aux;

}

void itoa(uint32_t value, char* str, uint32_t base) {

    static char num[] = "0123456789abcdefghijklmnopqrstuvwxyz";

    char* wstr=str;

    if (base<2 || base>35){ *wstr='\0'; return; }

    do *wstr++ = num[value%base]; while(value/=base);

    *wstr='\0';

    strreverse(str,wstr-1);

}
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
    while (!int_num) {
        if (int_num & 1) {
            count++;
        }
        int_num >>= 1;
    }
    return count;
}


uint32_t * get_zeros_pos(uint32_t vector, size_t vector_len, uint32_t * new_vector_len) {
    uint32_t * zeros_pos = malloc(vector_len * sizeof(uint32_t));
    size_t zeros_count = 0;
    for (size_t i = 0; i < vector_len; i++,vector>>=1) {
        if (!(vector%2)) {
            zeros_pos[zeros_count++] = vector_len - i;
        }
    }
    *new_vector_len = vector_len - zeros_count;
    zeros_pos = realloc(zeros_pos, zeros_count * sizeof(uint32_t));
    return zeros_pos;
}

uint32_t erase_zeros(uint32_t vector, const uint32_t * zeros_pos, uint32_t zeros_count) {
    char bin_vector[33];
    itoa(vector, bin_vector, 2);
    uint32_t bin_len = strlen(bin_vector);
    for (int64_t i = 0; i < zeros_count; i++) {
        uint32_t zero_pos = zeros_pos[i];
        if (zero_pos <= bin_len) {
            memmove(&bin_vector[zero_pos], &bin_vector[zero_pos+1],  bin_len - zero_pos);
            bin_len--;
        }
    }
    return strtol(bin_vector, NULL, 2);
}

uint32_t * delete_zeros(uint32_t * vectors,uint32_t vector_num, uint32_t vector_len,uint32_t * new_vector_len) {
    uint32_t vec_sum = 0;
    for (int i = 0; i < vector_num; i++) {
        vec_sum |= vectors[i];
    }
    uint32_t * zeros_pos = get_zeros_pos(vec_sum, vector_len, new_vector_len);
    uint32_t * new_vectors = (uint32_t *) malloc(vector_num * sizeof(uint32_t));
    for (size_t i = 0; i < vector_num; i++) {
        new_vectors[i] = erase_zeros(vectors[i], zeros_pos, vector_len-*new_vector_len);
    }
    free(zeros_pos);
    return new_vectors;
}
