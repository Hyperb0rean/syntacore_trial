#include "../include//io.h"
#include "../include/math.h"


int main() {

    uint32_t vector_num, vector_len;
    int32_t * vectors = read("/home/hyperb0rean/CLionProjects/syntacore_trial/input.txt", &vector_num, &vector_len);

    printf("Number of vectors: %d\n", vector_num);
    printf("Length of vectors: %d\n", vector_len);

    char* path = "spectrum.txt";

    write(vectors, path, vector_num);

    free(vectors);

    return 0;
}
