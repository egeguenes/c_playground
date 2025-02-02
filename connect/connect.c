#include <stdio.h>
#include <unistd.h>
#include <errno.h>

enum {
    READ = 0,
    WRITE = 1
};

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: connect <prog1> <prog2>\n");
        return -1;
    }
    int res, fd[2];
    if (pipe(fd) == 0) {
        res = fork();
        if (res > 0) {
            close(fd[READ]);
            dup2(fd[WRITE], 1);
            close(fd[WRITE]);
            execlp(argv[1], argv[1], NULL);
        } else if (res == 0) {
            close(fd[WRITE]);
            dup2(fd[READ], 0);
            close(fd[READ]);
            execlp(argv[2], argv[2], NULL);
        }
    }
    perror("Problem!\n");
}
