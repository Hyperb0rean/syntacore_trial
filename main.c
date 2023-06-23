#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>


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

int32_t * read(const char* path, uint32_t * vector_num, uint32_t * vector_len) {
    FILE* fin = fopen(path, "r");
    if (fin == NULL) {
        printf("Error opening file\n");
        exit(1);
    }

    char buffer[1024];
    int32_t count = 0;
    int32_t len = 0;
    while (fgets(buffer, sizeof(buffer), fin) != NULL) {
        count++;
        len = strlen(buffer);
    }
    rewind(fin);

    int32_t * vectors = (int32_t *) malloc(count * sizeof(int32_t));
    if (vectors == NULL) {
        printf("Error allocating memory\n");
        exit(1);
    }

    int32_t i = 0;
    while (fgets(buffer, sizeof(buffer), fin) != NULL) {
        vectors[i++] = strtol(buffer, NULL, 2);
    }

    fclose(fin);

    *vector_num = count;
    *vector_len = len - 1;

    return vectors;
}


void write(int32_t * output, char *path, size_t size) {
    FILE *fout = fopen(path, "w");
    for (size_t i = 0; i < size - 1; i++) {
        fprintf(fout, "%"  PRIu64  "\t%"PRId32"\n", i, output[i]);
    }
    fprintf(fout, "%"  PRIu64  "\t%"PRId32, size - 1, output[size - 1]);
    fclose(fout);
}

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
