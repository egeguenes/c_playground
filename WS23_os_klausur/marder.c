#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

void iterate_current_dir(void);
void handle_file(const char* filenmae);
void recurse(const char* path);
void die(const char* msg);

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <dir1> <dir2> <dir3> ... ", argv[0]);
        exit(EXIT_FAILURE);
    }

    for (int i=1; i<argc; i++) {
        recurse(argv[i]);
    }

    return 1;
}

void iterate_current_dir() {
    DIR *dir = opendir(".");
    if (!dir) {
        die("opendir");
    }

    struct dirent *ent;

    while ((ent=readdir(dir)) != NULL) {
        if (ent->d_name[0] == '.' || ent->d_name == '~') {
            continue;
        }
        if (ent->d_type == DT_REG) {
            handle_file(ent->d_name);
        } else if (ent->d_type == DT_DIR) {
            recurse(ent->d_name);
        }
    }
    closedir(dir);
}

void handle_file(const char* filename) {
    if (!strstr(filename, "good")) {
        pid_t pid = fork();
        if (pid < 0) {
            die("fork error");
        } else if (pid == 0) {
            execlp("trumpet", "trumpet", filename, NULL);
            die("execlp");
        } else {
            int status;
            wait(pid, &status, 0);
        }
    }
}

void recurse(const char* path) {
    iterate_current_dir();
}

void die(const char* msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}
