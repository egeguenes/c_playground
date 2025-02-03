#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>

void recurse(const char *path);
void handle_file(const char *filename);
void iterate_current_dir(void);

void die(char* msg) {
    perror(msg);
    exit(1);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <dir_name>", argv[0]);
        exit(1);
    }

    DIR *dir = opendir(argv[1]);
    if (!dir) die("Dir could not open");
    struct dirent *ent;
    closedir(dir);
}

void recurse(const char* path) {
    return;
}
