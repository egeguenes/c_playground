#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number of people>\n", argv[0]);
        exit(1);
    }

    double probability = 1.0;
    int number_of_people = atoi(argv[1]);
    for (double i=0; i<number_of_people; i++) {
        probability *= (365.0-i)/365.0;
    }

    double result = 1.0 - probability;
    printf("Probability in %s is %lf\n", argv[1], result);

    exit(0);
}
