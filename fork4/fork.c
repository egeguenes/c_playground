#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

// ** question why it prints like that
/*
        Current PID : 17742

 ->>    Printing the parent
        Child process PID : 17743 : mockpid: 0
        First print of child

        printing Child of child
        Child of child process PID 17744 : mockpid: 0
*/

int main() {
    pid_t pid;
    int status;

    printf("Current PID : %d\n\n", getpid());
    pid = fork();

    if (pid == 0) {
        printf("Child process PID : %d : mockpid: %d\n", getpid(), pid);
        printf("First print of child\n\n");
        pid_t pid2 = fork();
        int status2;
        if (pid2 == 0) {
            printf("printing Child of child\n");
            printf("Child of child process PID %d : mockpid: %d\n\n", getpid(), pid);
        } else if(pid2 > 0) {
            waitpid(pid2, &status2, 0);
        } else {
            perror("problem\n");
            return -1;
        }
    } else if(pid > 0) {
        printf("Printing the parent\n");
        waitpid(pid, &status, 0);
    } else {
        perror("problem\n");
        return -1;
    }
    return 0;
}
