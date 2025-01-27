#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid;
    pid = fork();

    if (pid > 0) {
        printf("Eltern: Warte auf Kind : %d\n", pid);
        int status;
        if (wait(&status) == pid && WIFEXITED(status)) {
            printf("Eltern: Exit status des Kindes : %d\n", WIFEXITED(status));
        } else {
            printf("Eltern: Kind nicht normal beendet\n");
        }
    } else if (pid == 0) {
        printf("Kind: beende mich in 10 Sekunden\n");
        sleep(10);
        printf("Kind: Jetzt");
        exit(42);
    } else {
        printf("Fehler");
    }
    return 0;
}
