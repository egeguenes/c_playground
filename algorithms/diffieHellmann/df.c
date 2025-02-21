#include "df.h"

#include <stdlib.h>
#include <unistd.h>
#include <math.h>

bool isPrime(int number);
int power_with_modulo(int base, int power, int modulo);

bool isPrime(int num) {
    for (int i=2; i<(int)sqrt(num); i++) {
        if (num % i == 0) return false;
    }
    return true;
}

int power_with_modulo(int base, int power, int mod) {
    while (power-- > 1) {
        base *= base;
        base = base%mod;
    }
    return base;
}
