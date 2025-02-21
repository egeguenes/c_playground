#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

/*
    Diffie-Hellmanm encryption implementation
*/

/*
    checks if the given number is prime
    param -> integer number to check
*/
bool isPrime(int number);

/*
    takes the given number to the power of the base and takes the modulo of it
    param -> integer base, integer exponential, integer modulo
*/
int power_with_modulo(int base, int exp, int mod);

void diffie_hellmann(int generator, int modulo, int alice_public, int bob_public);
