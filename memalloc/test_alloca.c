#include "tlpi_hdr.h"

int main() {
    int *p1 = (int *) malloc(sizeof(int));
    printf("malloc p1 = %p\n", p1);

    int *p2 = (int *) alloca(sizeof(int));
    printf("alloca p2 = %p\n", p2);

    int localVal = 10;
    printf("local variable address: %p\n", &localVal);

    exit(EXIT_SUCCESS);
}
