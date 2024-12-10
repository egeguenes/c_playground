#include <stdio.h>
#include <string.h>

int main() {
    char* output;
    char to_copy[] = "-12345678";
    int len_to_copy = strlen(to_copy);

    strncpy(output, to_copy+1, len_to_copy-1);
    output[len_to_copy - 1] = '\0';

    printf("Output should be without - : %s", output);

    return 0;
}
