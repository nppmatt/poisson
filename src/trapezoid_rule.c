/* src/trapezoid_rule.c */

#include <math.h>
#include <stdio.h>
#include "linalg_util.h"

/* Breaking off integrands into separate functions, as specified in problem. */
double quadratic(double x) {
	return x*x;
}

double sine(double x) {
	return sin(x);
}

double hardFunction(double x) {
	double sineResult = sin(x);
	return exp(-(SQR(sineResult)));
}

/* Error functions. */
double error_abs(double truth, double observed) {
	return fabs(truth - observed);
}

double error_rel(double truth, double observed) {
	return fabs((truth - observed) / truth);
}

/* Trapezoid rule with uniform spacing.
 * Parameters:
 * Integrand		- Pointer to C function we want to integrate over.
 * start, end		- Bounds of integration. Used to define grid/mesh.
 * numPartitions	- Number of steps for defining fineness of grid.
 *
 * Mesh is defined before performing integration to be pipeline/cache friendly.
 */
double trapezoid(double (*Integrand)(double), double start, double end, long numPartitions) {
	double result = 0;

	/* Define mesh. */
	double stepSize = (end - start) / (double) numPartitions;
	double mesh[numPartitions];
	for (long i = 0; i <= numPartitions; ++i) {
		mesh[i] = (double) i * stepSize;
	}

	/* Integrate with trapezoid rule. */
	for (long i = 1; i <= numPartitions; ++i) {
		result += ( (Integrand(mesh[i]) + Integrand(mesh[i-1])) * (0.5 * stepSize) );
	}

	return result;
}

int main() {
	const double L = 2.0 * M_PI;
	double integralResult = 0.0;
	double absError = 0.0;
	double relError = 0.0;

	/* Solving problems in (3a) */
	for (long N = 10; N <= 20; N+=10) {
		integralResult = trapezoid(&quadratic, 0.0, L, N);
		absError = error_abs( (L*L*L / 3), integralResult );
		relError = error_rel( (L*L*L / 3), integralResult );
		printf("x^2 with %d steps: %f | Abs. Error: %f | Rel. Error: %f\n",
				N, integralResult, absError, relError);

		integralResult = trapezoid(&sine, 0.0, L, N);
		absError = error_abs(0.0, integralResult);
		relError = error_rel(0.0, integralResult);
		printf("sin(x) with %d steps: %f | Abs. Error: %f | Rel. Error: %f\n",
				N, integralResult, absError, relError);
		printf("\n");
	}

	/* Solving problem (3b) */
	for (long N = 4; N <= 32; N*=2) {
		integralResult = trapezoid(&hardFunction, 0.0, L, N);
		printf("exp(-sin(x)^2) with %d steps: %f\n", N, integralResult);
		printf("\n");
	}

	return 0;
}

/* src/trapezoid_rule.c */

