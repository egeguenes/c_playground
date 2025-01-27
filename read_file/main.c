#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    char* line = NULL;
    size_t linelen = 0;
    if (argc < 2) {
        fprintf(stderr, "Usage %s FILE\n", argv[0]);
        exit(1);
    }

    FILE *infile = fopen(argv[1], "r");
    if (infile == NULL) {
        perror("Opening file");
        exit(1);
    }

    int line_counter = 0;
    while (getline(&line, &linelen, infile) != -1) {
        printf("%3d: %s", ++line_counter, line);
    }
    free(line);
    fclose(infile);
}
