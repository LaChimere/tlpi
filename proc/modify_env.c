#define _GNU_SOURCE
#include "tlpi_hdr.h"
#include <stdlib.h>

extern char **environ;

int main(int argc, char *argv[]) {
    int i;
    char **ep;

    clearenv();

    for (i = 0; i < argc; ++i) {
        if (putenv(argv[i]) != 0) {
            errExit("putenv: %s", argv[i]);
        }
    }

    if (setenv("GREET", "Hello world", 0) == -1) {
        errExit("setenv");
    }

    unsetenv("BYE");

    for (ep = environ; *ep != NULL; ++ep) {
        puts(*ep);
    }

    exit(EXIT_SUCCESS);
}
