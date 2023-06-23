#include <string.h>
#include <stdio.h>
#include <bits/mathcalls.h>
#include "../include/math.h"


void itoa(uint32_t value, char* str, uint32_t base, uint32_t len) {
    static char num[] = "0123456789abcdefghijklmnopqrstuvwxyz";
    char* wstr=str;
    if (base<2 || base>35){ *wstr='\0'; return; }
    for (int i = 0; i < len; ++i,value/=base) {
        *wstr++ = num[value%base];
    }
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
    while (int_num) {
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
    for (size_t i = 0; i < vector_len-1; i++,vector>>=1) {
        if (!(vector%2)) {
            zeros_pos[zeros_count++] = vector_len - i-1;
        }
    }
    *new_vector_len = vector_len - zeros_count;
    zeros_pos = realloc(zeros_pos, zeros_count * sizeof(uint32_t));
    return zeros_pos;
}

uint32_t erase_zeros(uint32_t vector, const uint32_t * zeros_pos, uint32_t zeros_count, uint32_t vector_len) {
    char bin_vector[vector_len];
    itoa(vector, bin_vector, 2,vector_len);
    uint32_t bin_len = strlen(bin_vector);
    for (int64_t i = 0; i < zeros_count; i++) {
        uint32_t zero_pos = zeros_pos[i];
        if (zero_pos <= bin_len) {
            memmove(&bin_vector[zero_pos], &bin_vector[zero_pos+1],  bin_len - zero_pos); //TODO: check if reverse ordering could be more efficient
            bin_len--;
        }
    }
    return strtol(bin_vector, NULL, 2);
}

uint32_t * delete_zeros(uint32_t * vectors,uint32_t vector_num, uint32_t vector_len,uint32_t * new_vector_len) {
    uint32_t vec_sum = 0;
    vector_len++;
    for (int i = 0; i < vector_num; i++) {
        vec_sum |= vectors[i];
    }
    uint32_t * zeros_pos = get_zeros_pos(vec_sum, vector_len, new_vector_len);
    uint32_t * new_vectors = (uint32_t *) malloc(vector_num * sizeof(uint32_t));
    for (size_t i = 0; i < vector_num; i++) {
        new_vectors[i] = erase_zeros(vectors[i], zeros_pos, vector_len-*new_vector_len,vector_len);
    }
    free(zeros_pos);
    return new_vectors;
}

uint32_t* get_basis(uint32_t * vectors, uint32_t vector_num, uint32_t vector_len, uint32_t * rank) {
    vector_len++;
    *rank = (vector_len < vector_num) ? vector_len : vector_num;
    for (uint32_t i = 0; i < *rank; ++i) {
        qsort(vectors,vector_num,sizeof (uint32_t),compare);
        uint32_t index = vector_len - 2;
        for (uint32_t j = 0; j < vector_num; ++j) {
            if ((vectors[j] & 1 << index) && (j != i)){
                vectors[j] ^= vectors[i];
            }
        }
    }
    uint32_t defect = 0;
    uint32_t * basis = (uint32_t*) malloc(*rank * sizeof(uint32_t));
    basis[0] = vectors[0];
    for (uint32_t i = 1; i < *rank; ++i) {
        if(vectors[i] != vectors[i-1]) basis[i] = vectors[i];
        else defect++;
    }
    *rank-=defect;
    return basis;
}

void find_spectrum(const uint32_t* basis, uint32_t vector_len, const uint32_t* bounds, uint32_t* total_spectrum) {
    uint32_t* spectrum = (uint32_t *) malloc((vector_len+1)*sizeof (uint32_t));
    uint32_t current_vector = 0;

    // Calculate the first vector in the given range and its weight
    if (bounds[0] != 0) {
        uint32_t i = 0;
        uint32_t gray = gray_encode(bounds[0]);
        while (gray) {
            if (gray % 2 == 1) {
                current_vector ^= basis[i];
            }
            i++;
            gray /= 2;
        }
    }
    spectrum[weight(current_vector)]++;

    // Calculate weights of other vectors
    for (uint32_t i = bounds[0]; i < bounds[1]; i++) {
        uint32_t bit_change_pos = (uint32_t)round(log2((-1-i) & (1+i)));
        current_vector ^= basis[bit_change_pos];
        uint32_t w = weight(current_vector);
        spectrum[w]++;
    }

    // Append weights from each process to the main list
    for (uint32_t i = 0; i < vector_len+1; i++) {
        *(total_spectrum + bounds[0] +i) = spectrum[i];
    }
}

uint32_t * process(uint32_t * basis, uint32_t rank, uint32_t new_vector_len,
                   uint32_t vector_len, uint32_t vector_num, uint32_t threads) {
    uint32_t *spectrum = (uint32_t *) malloc(vector_len * sizeof(uint32_t));
    memset(spectrum, 0, vector_len);
    if (rank == new_vector_len) {
        spectrum[0] = 1;
        for (uint32_t i = 1; i < rank + 1; i++) {
            spectrum[i] = (int) (spectrum[i - 1] * (rank - i + 1) / i);
        }
    } else {
        if (threads > 1) {
            printf("Using %d cores for parallel computing.\n", threads);
        } else {
            printf("Using 1 core for parallel computing.\n");
        }

//        uint32_t ** parts = blocks_partition(0,(1<<rank) -1,threads);
//#pragma omp parallel for num_threads(threads)
//        for (uint32_t i = 0; i < threads; i++) {
//            uint32_t start = parts[i];
//            end = (i == cores-1) ? part_size : parts[i+1];
//            for (j = start; j < end; j++) {
//                weight = 0;
//                for (k = 0; k < vector_len; k++) {
//                    if ((j >> k) & 1) {
//                        weight += basis[k];
//                    }
//                }
//                total_spectrum[weight] += 1;
//            }
//        }
//        free(parts);
//        for (i = 0; i < vector_len; i++) {
//            spectrum[i] = total_spectrum[i];
//        }
//    }
//    free(total_spectrum);
        for (uint32_t i = 0; i < vector_len; i++) {
            spectrum[i] = (int) (spectrum[i] * 1 << (vector_num - rank));
        }
    }
    return spectrum;
}