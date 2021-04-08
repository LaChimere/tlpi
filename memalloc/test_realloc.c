#include "tlpi_hdr.h"

int main() {
    int *p = (int *) calloc(4, sizeof(int));
    if (p == NULL) {
        errExit("calloc");
    }
    int *a = (int *) calloc(1, sizeof(int));
    *a = 10;

    int i;
    for (i = 0; i < 4; ++i) {
        p[i] = i << 1;
    }

    int *np = (int *) realloc(p, 20 * sizeof(int));
    if (np == NULL) {
        errExit("realloc");
    }
    printf("p = %p\n", p);
    printf("np = %p\n", np);

    exit(EXIT_SUCCESS);
}
