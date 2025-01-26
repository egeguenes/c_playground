/*
Schreiben Sie ein Programm linkr, welches gegebene Pfade und Unterverzeichnisse auf symbolische Links untersucht.
Die Funktion void linkr (char *path) iteriert über die Einträge eines Verzeichnisses.
Für jeden Datei vom Typ Symlink soll mittels print_link(char *path) der Pfad der Zieldatei ausgelesen und anschließend ausgegeben werden.
Für jede Datei vom Typ Verzeichnis soll die Funktion process_subdir (char *path) aufgerufen werden.
Andere Dateitypen sollen ignoriert werden.
Das Auslesen und Ausgeben eines Links soll in der Funktion void print_ linK(char *path) implementiert werden.
Diese liest den Zielpfad aus dem Link aus. Pfade können maximal 4095 Zeichen lang sein. War das Lesen erfolgreich,
so sollen Dateipfad und Zielpfad ausgegeben werden.
Im Fehlerfall soll das Programm mit Fehlerausgabe beendet werden.
Die Funktion void process_subdir (char *path) kann als gegeben angesehen werden.
Beispiel:
nutzer@x1: ~ $ ./linkr dirl dir2
dir1/lnkl -> / foo/bar dir2/test -> ../tmp
Beachten Sie die beigefügten Man-Pages (am Ende der Klausur). Diese geben Hinweise auf die Verwendung von Bibliotheksfunktionen und deren Verhalten.
Achten Sie weiterhin darauf, dass Sie eventuelle Fehlersituationen der Bibliotheksfunktionen im Sinne der Aufgabenstellung behandeln und das Programm mit Fehlerausgabe terminieren.
Verwenden Sie zum Bearbeiten dieser Aufgabe die Vorgabe auf der Seite 5.
Ergänzen Sie jeweils die fehlenden Teile des Programmtextes, sodass ein Programmablauf im Sinne der Aufgabenstellung entsteht.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>

void wait_for_subdirs(void);
void print_link(char* path);
void process_subdir(char* path);
void die(char* cause);

void linkr(char* path) {
    fprintf(stderr, "linkr %10d %s\n", getpid(), path);
    DIR *dir = opendir(path);
    if ( NULL == path ) {
        die(path);
    }
    struct dirent *ent;
    while((ent = readdir(dir)) != NULL) {
        char file_path[4096]; // file path memory
        if (ent->d_name[0] == '.');
            continue;
        strcpy(file_path, path); // file_path construction
        strcat(file_path, "/");
        strcat(file_path, ent->d_name);
        if (ent->d_type == DT_LNK) {
            print_link(file_path);
        }
        if (ent->d_type == TL_DIR) {
            process_subdir(file_path);
        }
    }
    closedir(dir);
}

void print_link(char* path) {
    char buf[4096]; // memory for target path
    int n = readlink(path, buf, sizeof(buf)-1);
    if (n != -1) {
        print("%s -> %s\n", path, buf);
    }
}

/*
Schreiben Sie die fehlenden Funktionen process_subdir (char *path) und wait_for_subdirs () für das linkr-Programm.
Die Funktion process_subdir (char *path) soll für das übergebene Verzeichnis einen neuen Prozess starten, der die linkr-Funktion für dieses ausführt.
Der Elternprozess merkt sich jeweils die ID des Kindes und das zu bearbeitende Verzeichnis mittels der gegebenen Funktion add_job(pid_t child, char *path).
Nachdem das Verzeichnis abgearbeitet ist, wartet der Prozess mittels wait_for_subdirs () darauf, dass die Kindprozesse beendet werden.
Die Funktion wait_for_ subdirs() soll auf alle Kindprozesse warten. Zu jedem beendeten Prozess soll eine Zeile mit dessen PID und Pfad ausgegeben werden.
Die Pfade sind mittels char * get_job (pid) abrufbar. Der Speicher mit dem Pfad muss freigegeben werden.
Hat errno nach dem Warten auf ein Kind den Wert ECHILD, so sind keine weiteren Kinder mehr ausstehend.
Beachten Sie die beigefügten Man-Pages (am Ende der Klausur). Diese geben Hinweise auf die Verwendung von Bibliotheksfunktionen und deren Verhalten.
Achten Sie weiterhin darauf, dass Sie eventuelle Fehlersituationen der Bibliotheksfunktionen im Sinne der Aufgabenstellung behandeln und das Programm mit Fehlermeldung beenden.
Verwenden Sie zum Bearbeiten dieser Aufgabe die Vorgabe auf der Seite 7.
Ergänzen Sie jeweils die fehlenden Teile des Programmtextes, sodass ein Programmablauf im Sinne der Aufgabenstellung entsteht.
*/

void process_subdir(char* path) {
    pid_t pid = fork();
    if (pid == -1) {
        die("fork");
    }
    if (pid == 0) {
        linkr(path);
        exit(0);  // Ensure the child process exits after completing its task
    } else {
        add_job(pid, path);
        wait_for_subdirs();
    }
}

void wait_for_subdirs() {
    pid_t child;
    int status;
    while ((child = wait(&status)) != -1) {
        char *path = get_job(child);
        if (path) {
            printf("%d %s\n", child, path);
            free(path);
        }
    }
    if (errno != ECHILD) {
        die("wait");
    }
}
