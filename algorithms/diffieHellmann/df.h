#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

/*
    Diffie-Hellmanm encryption implementation
*/

/*
    checks if the given number is prime
    param -> integer number to check
    returns boolean
*/
bool isPrime(int number);

/*
    takes the given number to the power of the base and takes the modulo of it
    param -> integer base, integer exponential, integer modulo
    returns integer
*/
int power_with_modulo(int base, int exp, int mod);

/*
    exponential function, takes an integer as base and exponential and gives the result as long int
    param -> integer base, integer exponential
    returns long int
*/
long int power_func(int base, int exp);

/*
    Diffie-Hellman encryption-decryption algorithm where
        generator^(alice private key a) mod modulo prime equals to alice_public
        generator^(bob private key b) mod modulo prime equals to bob_public
    param -> integer generator number, integer modulo prime, integer alica public key, integer bob public key
    no return value
*/
void diffie_hellman(int generator, int modulo, int alice_public, int bob_public);
