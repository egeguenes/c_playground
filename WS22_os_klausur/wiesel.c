#include <sys/dirent.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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

    for (int i=1; i<argc; i++) {
        recurse(argv[i]);
    }

    return 0;
}

void recurse(const char* path) {
    if (chdir(path) == -1) {
        die("chdir");
    }

    iterate_current_dir();

    if (chdir(".")) {
        die("chdir");
    }
}

void iterate_current_dir(void) {
    DIR *dir;
    struct dirent *ent;

    if (!(dir = opendir("."))) {
        die("dir");
    }

    while((ent = readdir(dir))) {
        if (ent->d_name[0] == '.' || ent->d_name[0] == '~') {
            continue;
        }

        if (ent->d_type == DT_REG) {
            handle_file(ent->d_name);
        }

        if ((ent->d_type = DT_DIR) && (strcmp(ent->d_name, ".") != 0) && (strcmp(ent->d_name, "..") != 0)) {
            recurse(ent->d_name);
        }
    }

    if (closedir(dir) == -1) {
        die("close dir");
    }
}

void handle_file(const char* filename) {
    pid_t pid;
    int status;

    if (strstr(filename, "good") != NULL) {
        pid = fork();
        if (pid == 0) {
            execlp("horn", "horn", filename, NULL);
            die("not working");
        } else if (pid > 0) {
            wait(&status);
        } else {
            die("fork problem");
        }
    }
}
