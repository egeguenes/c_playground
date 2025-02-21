#include "df.h"

#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]) {

    int alice = 17;
    int bob = 23;
    int mod = 31;
    int gen = 12;

    for (int i=1; i<mod; i++) {
        if (power_with_modulo(gen, i, gen) == alice) {
            for (int j=1; j<mod; j++) {
                if (power_with_modulo(gen, j, mod) == bob) {
                    int result = power_with_modulo(gen, i*j, mod);
                    printf("Alice private is -> %d\nBob private is -> %d\nThe secret is -> %d\n", i, j, result);
                    exit(0);
                }
            }
        }
    }
    exit(1);
}
