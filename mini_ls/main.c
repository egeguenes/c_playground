#include <stdio.h>
#include <dirent.h>

int main() {
    DIR *dir = opendir(".");
    struct dirent *ent;

    while ((ent = readdir(dir)) != NULL) {
        printf("File : %s\n", ent->d_name);
    }
    closedir(dir);
    return 0;
}
