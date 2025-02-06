#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

void die(char* msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

void handle_file(char* filename) {
    struct stat lst;

    if (lstat(filename, &lst) == -1) {
        die("some problem!");
    }

    if (lst.st_size < 1024) {
        printf("File name: %s,\nFile size: %lld Bytes\n", filename, lst.st_size);
    }
}

int main(int argc, char* argv[]) {
    DIR *dir = opendir(".");
    if (!dir) {
        die("opendir problem!");
    }

    struct dirent *ent;
    while((ent = readdir(dir)) != NULL) {
        if (ent->d_type == DT_REG || ent->d_type == DT_LNK) {
            handle_file(ent->d_name);
        }
    }

    closedir(dir);
    return 1;
}
