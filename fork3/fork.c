#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();
    fork();

    if (pid > 0) {
        printf("pid !=> 0 : %d\n", getpid());
    }
    if (pid == 0) {
        printf("pid ==> 0 : %d\n", getpid());
    }

    printf("abc\n");
    return 0;
}
