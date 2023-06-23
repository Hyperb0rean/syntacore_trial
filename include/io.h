
#ifndef SYNTACORE_TRIAL_IO_H
#define SYNTACORE_TRIAL_IO_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

void write(int32_t * output, char *path, size_t size);
int32_t * read(const char* path, uint32_t * vector_num, uint32_t * vector_len);

#endif //SYNTACORE_TRIAL_IO_H
