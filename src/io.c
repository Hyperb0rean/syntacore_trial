#include "../include/io.h"


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