#include "tlpi_hdr.h"
#include <sys/stat.h>
#include <fcntl.h>

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

int main(int argc, char *argv[]) {
    int *fds, openFlags, ap, numFd, i, numRead;
    mode_t filePerms;
    char buf[BUF_SIZE];

    if (argc < 2 || strcmp(argv[1], "--help") == 0) {
        usageErr("%s files... or %s -a files...\n", argv[0], argv[0]);
    }

    openFlags = O_CREAT | O_WRONLY;
    filePerms = 0666;
    if (strcmp(argv[1], "-a") == 0) {
        ap = 2;
        openFlags |= O_APPEND;
    } else {
        ap = 1;
        openFlags |= O_TRUNC;
    }
    numFd = argc - ap;
    fds = (int *)malloc(sizeof(int) * numFd);

    for (i = 0; i < numFd; ++i) {
        fds[i] = open(argv[ap++], openFlags, filePerms);
        if (fds[i] == -1) {
            errExit("open");
        }
    }

    while ((numRead = read(STDIN_FILENO, buf, BUF_SIZE)) > 0) {
        if (write(STDOUT_FILENO, buf, numRead) != numRead) {
            fatal("write");
        }
        for (i = 0; i < numFd; ++i) {
            if (write(fds[i], buf, numRead) != numRead) {
                fatal("write");
            }
        }
    }
    if (numRead == -1) {
        errExit("read");
    }

    for (i = 0; i < numFd; ++i) {
        if (close(fds[i]) == -1) {
            errExit("close");
        }
    }
    free(fds);
    exit(EXIT_SUCCESS);
}
