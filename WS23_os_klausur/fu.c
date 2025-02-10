#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

#define true 1
#define false 0

void die(char *msg);
int handle_proc(char* pid, char *path);

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s PATH", argv[0]);
        exit(1);
    }

    char *path = argv[1];
    DIR *proc_dir = opendir(".");
    if (!proc_dir) {
        die("opendir");
    }

    struct dirent *ent;
    while ((ent = readdir(proc_dir)) != NULL) {
        if (ent->d_type == DT_DIR) {
            if (strspn(ent->d_name, "0123456789") == strlen(ent->d_name)) {
                if (handle_proc(ent->d_name, path)) {
                    printf("%s\n", ent->d_name);
                }
            }
        }
    }
    closedir(dir);

    return 0;
}

int handle_proc(char* pid, char* path) {
    char fd_path[256], target[256];
    ssize_t len;

    snprintf(fd_path, sizeof(fd_path), "%s/fd/1", pid);
    len = readlink(fd_path, target, sizeof(target)-1);

    if (len == -1) {
        return false;
    }

    target[len] = '\0';

    return strcmp(target, path) == 0;
}

void die(char* msg) {
    perror(msg);
    exit(1);
}
