
#ifndef SYNTACORE_TRIAL_MATH_H
#define SYNTACORE_TRIAL_MATH_H
#include <inttypes.h>
#include <stdlib.h>

uint32_t gray_encode(uint32_t g);
uint32_t gray_decode(uint32_t gray);

uint32_t weight(uint32_t int_num);
uint32_t * delete_zeros(uint32_t * vectors,uint32_t vector_num,uint32_t vector_len,uint32_t* new_vector_len);




#endif //SYNTACORE_TRIAL_MATH_H
