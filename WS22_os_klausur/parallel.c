#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

typedef struct job {
    int invalid;
    char *input;
    size_t input_length;
    char **argv;
} job_t;

int getNextJob(int fd, job_t *job);
void die(char* msg);
void freeJob(job_t *job);
void bury(void);

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file1> <file2> ... ", argv[0]);
        exit(1);
    }

    for (int i=1; i<argc; i++) {

    }

}

void bury(void) {
    int status;
    pid_t pid;
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        printf("Exited pid=%d, exitstatus=%d\n", pid, WIFEXITED(status));
    }
}

void die(char* msg) {
    perror(msg);
    exit(1);
}
