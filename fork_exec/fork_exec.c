#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

int main() {
    pid_t pid;
    char cmd[100], args[100];
    while (1) {
        printf("Kommando?\n");
        scanf("%99s %99s", cmd, args);
        pid = fork();

        if (pid > 0) {
            printf("Eltern: Warte auf Kind %d\n", pid);
            int status;
            if (wait(&status) == pid && WIFEXITED(status)) {
                printf("Eltern: Exit status des Kindes %d", WIFEXITED(status));
            } else {
                printf("Eltern: Kind nicht normal beendet\n");
            }
        } else if (pid == 0) {
            printf("Kind: Starte das Kommando\n");
            execlp(cmd, cmd, args, NULL);
            printf("Kind: exec fehlgeschlagen\n");
            exit(ENOENT);
        } else {
            printf("Oh no ein Fehler\n");
        }
    }
}
