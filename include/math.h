
#ifndef SYNTACORE_TRIAL_MATH_H
#define SYNTACORE_TRIAL_MATH_H
#include <inttypes.h>
#include <stdlib.h>

uint32_t weight(uint32_t int_num);
uint32_t * delete_zeros(uint32_t * vectors,uint32_t vector_num,uint32_t vector_len,uint32_t* new_vector_len);
uint32_t * get_basis(uint32_t * vectors, uint32_t vector_num, uint32_t vector_len, uint32_t * rank);


#endif //SYNTACORE_TRIAL_MATH_H
