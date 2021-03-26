#include "tlpi_hdr.h"
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    int fd, numWritten;

    if (argc != 3 || strcmp(argv[1], "--help") == 0) {
        usageErr("%s filename input\n", argv[0]);
    }

    fd = open(argv[1], O_WRONLY);
    if (fd == -1) {
        errExit("open");
    }

    numWritten = pwrite(fd, argv[2], strlen(argv[2]), SEEK_SET);
    if (numWritten == -1) {
        errExit("pwrite");
    }
    if (numWritten < strlen(argv[2])) {
        printf("Write fewer bytes than input\n");
    }

    if (close(fd) == -1) {
        errExit("close");
    }

    exit(EXIT_SUCCESS);
}
