#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MBYTE (1024*1024)

int main() {
    char* p_array[20];
    size_t size = 100 * MBYTE;
    for (int i=0; i<20; i++) {
        p_array[i] = (char*)(malloc(size));
        if (!p_array[i]) {
            perror("could not allocate the memory\n");
            exit(EXIT_FAILURE);
        }
        printf("size -> %lu : adress -> %p\n", size, &p_array[i]);
    }
    for (int i=0; i<20; i++) {
        free(p_array[i]);
    }
    return 0;
}
