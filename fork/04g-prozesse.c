#include <stdio.h>
#include <stdlib.h>
#include <sys/syslimits.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_LEN 128
#define MAX_ARGS 10
#define DELIMITER ' '
#define STRING_CHAR '\"'
#define ESCAPE_CHAR '\\'
#define QUIT_COMMAND "exit"

// str is the given array, len is the length of it
void print_strarray(char* str[], int len) {
    printf("{");
    for (int i=0; i < len-1; i++) {
        printf("%s", str[i]);
    }
    printf("%s}\n", str[len-1]);
}

int strsplit(char* buf[], int size, char* str, int len, char deli, char escape, char tstring) {
    int count = 0;
    short joinstr;
    buf[0] = str;
    for (int i=0; i<len; i++) {
        if (tstring && str[i] == tstring) joinstr = !joinstr;
        if (joinstr) continue;

        if (str[i] != deli) continue;
        if (escape && i-1>=0 && str[i-1] == escape) continue;

        while (str[i+1] == deli) {
            i++;
        }

        if (i+1 >= len) return count+1;

        count++;
        if (count>=size) return size;
        buf[count] = &str[i+1];
    }
    return count+1;
}

int main(void) {
    char in[MAX_INPUT_LEN];

    while(fgets(in, MAX_INPUT_LEN, stdin)) {
        int in_len = strlen(in);
        in[in_len-1] = '\0';

        if (in_len == 0) continue;
        if (!strcmp(in, QUIT_COMMAND)) break;

        char* args[MAX_ARGS];
        int args_size = strsplit(args, MAX_ARGS, in, in_len, DELIMITER, ESCAPE_CHAR, STRING_CHAR);

        args[args_size] = NULL;
        print_strarray(args, args_size);

        pid_t pid = fork();
        if (pid==0) {
            if (execvp(args[0], args) < 0) {
                perror("execyp");
                return EXIT_FAILURE;
            }
        } else if (pid > 0) {
            int status;

            if (wait(&status) < 0) {
                perror("wait");
                return EXIT_FAILURE;
            }
            printf("\"%s\" = %i\n", in, status);
        } else {
            perror("fork");
            return EXIT_FAILURE;
        }
    }
    if (ferror(stdin)) {
        perror("ferror");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
