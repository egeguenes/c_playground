#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Usage: %s <program> <num1> <operator> <num2>\n", argv[0]);
        return -1;
    }

    char* args[] = {argv[1], argv[2], argv[3], argv[4], NULL};

    printf("Program has started! Program: %s : PID: %d\n", argv[0], getpid());

    pid_t pid = fork();
    int status;

    if (pid == 0) {
        printf("This is the child Process! PID: %d\n", getpid());
        execv("./other", args);
        perror("execv failed");  // If execv fails, print error and exit
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        waitpid(pid, &status, 0);
        printf("This is the parent process -> PID: %d\n", getpid());

        if (WIFEXITED(status)) {
            printf("Child exited with status: %d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Child was terminated by signal: %d\n", WTERMSIG(status));
        }
    } else {
        perror("Fork failure!");
        return -1;
    }

    return 0;
}
