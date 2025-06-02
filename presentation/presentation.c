#include <stdio.h>

float Q_rsqrt( float number ) {
	int i;
	float x2, result;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	result  = number;
	i  = * ( long * ) &result;                // predict num as long
	i  = 0x5f3759df - ( i >> 1 );               // subtract half of the long num from magical num
	result  = * ( float * ) &i;
	printf("current result before any iteration is %f\n", result);
	result  = result * ( threehalfs - ( x2 * result * result ) );   // 1st iteration
	printf("result after 1 iteration %f\n", result);
	//result  = result * ( threehalfs - ( x2 * result * result ) );   // 2nd iteration, this can be removed
	//printf("result after 2 iteration %f\n", result);

	return result;
}

int main() {
    int i;
    float f = 123.124412;
    printf("My float is: %f\n", f);
    printf("Expected answer would be %f\n", 1/f);
    float sq_f = f * f;
    printf("Square of the float is %f\n", sq_f);

    float answer = Q_rsqrt(sq_f);

    return 0;
}
