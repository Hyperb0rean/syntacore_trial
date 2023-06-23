#include "../include//io.h"
#include "../include/math.h"


int main() {

    uint32_t vector_num, vector_len;
    uint32_t * vectors = read("/home/hyperb0rean/CLionProjects/syntacore_trial/input.txt", &vector_num, &vector_len);

    printf("Number of vectors: %d\n", vector_num);
    printf("Length of vectors: %d\n", vector_len);

    char* path = "spectrum.txt";


    uint32_t new_vector_len;
    uint32_t * new_vectors = delete_zeros(vectors,vector_num,vector_len,&new_vector_len);


//    for (int i = 0; i < vector_num; ++i) {
//        vectors[i] = weight(vectors[i]);
//    }
    write(new_vectors, path, vector_num);

    free(vectors);
    free(new_vectors);
    return 0;
}
