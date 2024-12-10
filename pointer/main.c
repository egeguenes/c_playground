#include <stdio.h>

int main(void) {
    char *str = "Hello";
    printf("%c\n", *str + 1); // *str -> 'H' + 1 -> char to int conversion and then int to char
    printf("%s\n", str + 1); // print starting from the first index
    return 0;
}
