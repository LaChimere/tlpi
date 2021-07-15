#include "tlpi_hdr.h"
#include <signal.h>

static void sigHandler(int sig) {
    printf("ouch: %s\n", strsignal(sig));
}

int main() {
    int j;

    if (signal(SIGINT, sigHandler) == SIG_ERR) {
        errExit("signal");
    }

    for (j = 0; ; j++) {
        printf("%d\n", j);
        sleep(3);
    }

    exit(EXIT_SUCCESS);
}
