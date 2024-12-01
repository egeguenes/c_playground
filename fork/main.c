#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid;
    pid = fork();

    if (pid > 0) {
        printf("Elter: Warte auf Kind %d\n", pid);
        int status;
        if (wait(&status) == pid && WIFEXITED(status)) {
            printf("Elter: Exit status des Kindes %d\n", WEXITSTATUS(status));
        } else {
            printf("Elter: Kind nicht normal beendet :-(\n");
        }
    } else if (pid == 0) {
        printf("Kind: beende mich in 10 Sekunden mit 42\n");
        sleep(10);
        printf("Kind: Jetzt :-(\n");
        exit(42);
    } else {
        printf("Oh, ein Fehler!\n");
    }
}
// trying something about git
// diff
