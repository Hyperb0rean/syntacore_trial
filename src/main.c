#include "../include//io.h"
#include "../include/math.h"
#include "../include/utils.h"

int main() {

    uint32_t vector_num, vector_len;
    uint32_t * vectors = read("/home/hyperb0rean/CLionProjects/syntacore_trial/input.txt", &vector_num, &vector_len);

    printf("Number of vectors: %d\n", vector_num);
    printf("Length of vectors: %d\n", vector_len);

    char* path = "spectrum.txt";


    uint32_t new_vector_len;
    uint32_t * new_vectors = delete_zeros(vectors,vector_num,vector_len,&new_vector_len);


    uint32_t rank;
    uint32_t * basis = get_basis(new_vectors,vector_num,new_vector_len,&rank);
//    for (int i = 0; i < vector_num; ++i) {
//        new_vectors[i] = weight(new_vectors[i]);
//    }
//    write(new_vectors, path, new_vector_len);

    //write(basis, path, rank);
    uint32_t* spectrum = process(basis,rank,new_vector_len,vector_len,vector_num,2);

    write(spectrum, path, vector_len+2);


    free(spectrum);
    free(basis);
    free(vectors);
    free(new_vectors);
    return 0;
}
