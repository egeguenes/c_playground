#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <num1> <operator> <num2>\n", argv[0]);
        return -1;
    }

    int first = atoi(argv[1]);
    int second = atoi(argv[3]);

    printf("Process: %s : PID: %d\n", argv[0], getpid());
    printf("Calculating\n");
    for(int i = 0; i < 3; i++) {
        sleep(1);
        printf("...\n");
    }

    switch(argv[2][0]) {
        case 'x':
            printf("The result is %d\n", first * second);
            break;
        case '+':
            printf("The result is %d\n", first + second);
            break;
        case '/':
            if (second == 0) {
                fprintf(stderr, "Error: Division by zero!\n");
                return -1;
            }
            printf("The result is %f\n", (float)first / second);
            break;
        case '-':
            printf("The result is %d\n", first - second);
            break;
        default:
            fprintf(stderr, "Error: Invalid operator!\n");
            return -1;
    }

    return 0;
}
