#include <dirent.h>
#include <stdio.h>

int print_dirs(const char *path) {
    DIR *dir = opendir(path);
    struct dirent *e = NULL;

    while ( (e = readdir(dir)) ) {
        printf("%s\t%d\n" , e->d_name, (int)e->d_ino);
    }

    closedir(dir); 

    return 0;
}
