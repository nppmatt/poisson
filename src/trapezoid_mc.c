/* src/trapezoid_mc.c */

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include "linalg_util.h"

double hardFunction(double x) {
	double sineResult = sin(x);
	return exp(-(SQR(sineResult)));
}

int main() {
	/* Linear Congruential Generator based on Donald Knuth's MMIX virtual machine
	 * is used to generate pseudorandom numbers for Monte-Carlo.
	 */
	const uint64_t multiply = 6364136223846793005;
	const uint64_t increment = 1;
	const uint64_t seed = 31254066;
	uint64_t lcgState = seed;
	double myUniform = 0.0;

	/* Still using original integral bound. */
	const double L = 2.0 * M_PI;

	/* Solving problem (3b) with Monte-Carlo integration. */
	double integralResult = 0.0;
	const long iterations = 32;
	for (long N = 0; N < iterations; ++N) {
		/* Update LCG */
		lcgState = multiply * lcgState + increment;
		myUniform = (double) lcgState / (double) UINT64_MAX;

		/* Integrate to get expected value later. */
		integralResult += hardFunction(L * myUniform);
	}
	integralResult = L * integralResult / (double) iterations;
	printf("exp(-sin(x)^2) with %d iterations of Monte-Carlo: %f\n", iterations, integralResult);
	printf("\n");

	return 0;
}

/* src/trapezoid_mc.c */

