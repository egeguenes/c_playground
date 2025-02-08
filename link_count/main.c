#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int getNumLinks(const char* filename);

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file/path> ...\n", argv[0]);
        exit(1);
    }

    for(int i=1; i<argc; i++) {
        const char* filename = argv[i];
        int num = getNumLinks(filename);
        if (num == -1) {
            fprintf(stderr, "Error: %s\n", strerror(errno));
        } else {
            printf("%s: %d\n", filename, num);
        }
    }
    exit(0);
}

int getNumLinks(const char* filename) {
    struct stat *st;
    if (stat(filename, st) == -1) {
        return -1;
    }
    return st->st_nlink;
}
