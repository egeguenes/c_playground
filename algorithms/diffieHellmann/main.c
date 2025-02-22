#include "df.h"

#include <unistd.h>
#include <stdio.h>

int main(int argc, char* argv[]) {

    if (argc != 5) {
        fprintf(stderr, "Usage: %s <generator_number> <modulo_number> <alica_public_key> <bob_public_key>\n", argv[0]);
        exit(1);
    }

    int gen = atoi(argv[1]);
    int mod = atoi(argv[2]);
    int alice = atoi(argv[3]);
    int bob = atoi(argv[4]);

    diffie_hellman(gen, mod, alice, bob);

    exit(0);
}
