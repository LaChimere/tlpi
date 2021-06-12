#define _BSD_SOURCE
#include "file_perms.h"
#include "tlpi_hdr.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

static void displayStatInfo(const struct stat *sb) {
    printf("File type:            ");
    switch (sb->st_mode & S_IFMT) {
        case S_IFREG:
            puts("regular file");
            break;
        case S_IFDIR:
            puts("directory");
            break;
        case S_IFCHR:
            puts("character device");
            break;
        case S_IFBLK:
            puts("block device");
        case S_IFLNK:
            puts("symbolic (soft) link");
            break;
        case S_IFIFO:
            puts("FIFO or pipe");
        case S_IFSOCK:
            puts("socket");
            break;
        default:
            puts("unknown file type?");
            break;
    }

    printf("Device containing i-node: major=%ld, minor=%ld\n",
           (long) major(sb->st_dev), (long) minor(sb->st_dev));

    printf("I-node number:        %ld\n", (long) sb->st_ino);

    printf("Mode:                 %lo (%s)\n",
           (unsigned long) sb->st_mode, filePermStr(sb->st_mode, 0));

    if (sb->st_mode & (S_ISUID | S_ISGID | S_ISVTX)) {
        printf("    special bits set:    %s%s%s\n",
               (sb->st_mode & S_ISUID) ? "set-UID " : "",
               (sb->st_mode & S_ISGID) ? "set-GID " : "",
               (sb->st_mode & S_ISVTX) ? "set-VTX " : ""
        );
    }

    printf("Number of (hard) links:    %ld\n", (long) sb->st_nlink);

    printf("Ownership:        UID=%ld, GID=%ld\n",
           (long) sb->st_uid, (long) sb->st_gid);

    if (S_ISCHR(sb->st_mode) || S_ISBLK(sb->st_mode)) {
        printf("Device number (st_rdev):  major=%ld, minor=%ld\n",
               (long) major(sb->st_rdev), (long) minor(sb->st_rdev));
    }

    printf("File size:              %lld bytes\n", (long long) sb->st_size);
    printf("Optimal I/O block size: %ld bytes\n", (long) sb->st_blksize);
    printf("512 B blocks allocated: %lld\n", (long long) sb->st_blocks);
    printf("Last file access:       %s", ctime(&sb->st_atim));
    printf("Last file modification: %s", ctime(&sb->st_mtim));
    printf("Last status change:     %s", ctime(&sb->st_ctim));
}

int main(int argc, char *argv[]) {
    struct stat sb;
    Boolean statLink;
    int fname;

    statLink = argc > 1 && strcmp(argv[1], "-l") == 0;
    fname = statLink ? 2 : 1;
    if (fname >= argc || (argc > 1 && strcmp(argv[1], "--help") == 0)) {
        usageErr("%s [-l] file\n"
                 "        -l = use lstat() instead of stat()\n", argv[0]);
    }

    if (statLink) {
        if (lstat(argv[fname], &sb) == -1) {
            errExit("lstat");
        }
    } else {
        if (stat(argv[fname], &sb) == -1) {
            errExit("stat");
        }
    }

    displayStatInfo(&sb);

    exit(EXIT_SUCCESS);
}
