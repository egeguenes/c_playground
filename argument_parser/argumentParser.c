#include "argumentParser.h"

// TODO -arg should be accepted but bc of -arg-a should not be accepted we got problems!
// command -arg -opt=val arg_sh (arg_sh should not be accepted!)

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>

// max argument size for c
#define MAX_SIZE 127

// init the values to be used
static char** args = NULL;
static char* command = NULL;
static int num_of_args = 0;
static int num_of_opts = 0;

// a new structure for saving the key and value together
struct key_value {
    char key[MAX_SIZE];
    char value[MAX_SIZE];
} key_value;
struct key_value dict[MAX_SIZE];

// a boolean function to see if a given string of given length includes the given char
bool includes(int len, char* arg, char ch) {
    return strchr(arg, ch);
}

// a function to add key value pair to the structure
void addKeyValue(int len, char* arg) {
    // checking if = char in the string
    char *equalSign = strchr(arg, '=');

    if (equalSign != NULL) {
        // if yes add the option to the key attribute, not starting from - using pointer arithmetic
        strncpy(dict[num_of_opts].key, arg+1, equalSign-arg-1);
        dict[num_of_opts].key[equalSign-arg-1] = '\0'; // null termination
        strncpy(dict[num_of_opts].value, equalSign+1, len - (equalSign-arg+1)); // doing the same for the value
        dict[num_of_opts].value[len - (equalSign-arg+1)] = '\0'; // null termination
    } else {
        // otherwise, just save the option without a value
        strncpy(dict[num_of_opts].key, arg, len-1);
        dict[num_of_opts].key[len-1] = '\0';
        strcpy(dict[num_of_opts].value, "");
    }
    num_of_opts++;
}

int initArgumentParser(int argc, char* argv[]) {
    if (argc < 1) {
        errno = EINVAL;
        return -1;
    }
    bool no_more_args; // boolean flag for no args, so that we dont get any arg at the end
    args = argv;
    command = argv[0];

    for (int i=1; i<argc; i++) {
        // if has - and includes = then it is a key value
        if (argv[i][0] == '-' && includes(strlen(argv[i]), argv[i], '=')) {
            addKeyValue(strlen(argv[i]), argv[i]);
            no_more_args = true;
        } else {
            if (no_more_args) { // modify no more args flag
                return -1;
            }
            num_of_args++;
        }
    }
    return 0;
}

// returns the command, which is argument 0
char* getCommand(void) {
    return command;
}

// returns the number of arguments
int getNumberOfArguments(void) {
    return num_of_args;
}

//returns the argument on the index
char* getArgument(int index) {
    if (index >= num_of_args || index < 0) {
        return NULL;
    }
    return args[index+1];
}

char* getValueForOption(char* keyName) {
    for (int i=0; i<num_of_opts; i++) {
        if (strcmp(keyName, dict[i].key) == 0) {
            return dict[i].value;
        }
    }
    return NULL;
}
