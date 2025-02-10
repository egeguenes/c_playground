#include <stdio.h>
#include <unistd.h>

int main() {
    fork();
    fork();
    fork();
    printf("SA AS\n");
    return 1;
}   