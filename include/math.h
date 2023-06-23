
#ifndef SYNTACORE_TRIAL_MATH_H
#define SYNTACORE_TRIAL_MATH_H
#include "utils.h"

uint32_t * delete_zeros(uint32_t * vectors,uint32_t vector_num,uint32_t vector_len,uint32_t* new_vector_len);
uint32_t * get_basis(uint32_t * vectors, uint32_t vector_num, uint32_t vector_len, uint32_t * rank);
uint32_t * process(uint32_t * basis, uint32_t rank, uint32_t new_vector_len,
                   uint32_t vector_len, uint32_t vector_num, uint32_t threads);

#endif //SYNTACORE_TRIAL_MATH_H
