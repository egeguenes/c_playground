#include "df.h"

#include <unistd.h>
#include <math.h>
#include <stdio.h>

bool isPrime(int number);
int power_with_modulo(int base, int power, int modulo);
long int power_func(int base, int exp);
void diffie_hellman(int generator, int modulo, int alice_public, int bob_public);

bool isPrime(int num) {
    if (num <= 1) return false;
    for (int i=2; i<(int)sqrt(num); i++) {
        if (num % i == 0) return false;
    }
    return true;
}

int power_with_modulo(int base, int power, int mod) {
    while (power-- > 1) {
        base = (base*base)%mod;
    }
    return base;
}

long int power_func(int base, int exp) {
    long int result = (long int)base;
    while (exp-- > 1) {
        result *= base;
    }
    return result;
}

void diffie_hellman(int generator, int modulo, int alice_public, int bob_public) {
    if (generator<=1 || !isPrime(modulo) || (alice_public>=modulo || alice_public<1) || (bob_public>=modulo || bob_public<1)) {
        fprintf(stderr, "Invalid input!\n");
        exit(1);
    }

    for (int i=1; i<modulo; i++) {
        if (power_with_modulo(generator, i, modulo) == alice_public) {
            for (int j=1; j<modulo; j++) {
                if (power_with_modulo(generator, j, modulo) == bob_public) {
                    int result = power_with_modulo(generator, i*j, modulo);
                    printf("First private is -> %d\nSecond private is -> %d\nThe secret is -> %d\n", i, j, result);
                    return;
                }
            }
        }
    }

    printf("No solution could be found!\n");
}
