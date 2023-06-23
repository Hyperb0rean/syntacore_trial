#include <stdio.h>

unsigned int grayencode(unsigned int g)
{
    return g ^ (g >> 1);
}

unsigned int graydecode(unsigned int gray)
{
    unsigned int bin;
    for (bin = 0; gray; gray >>= 1) {
        bin ^= gray;
    }
    return bin;
}


int main() {
    unsigned int code = 0;
    scanf("%d", &code);
    printf("Gray code: %d", grayencode(code));
    return 0;
}
