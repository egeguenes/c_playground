#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    for(int i=0; i<4; i++) {
        fork();
    }
    printf("id : %d\n", getpid());
    printf("aa");
}
