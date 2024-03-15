/* src/hilbert_multiply.c */

#include <stdio.h>
#include "linalg_util.h"

int main() {
	const long N = 6;

	/* Matrices are defined using the scheme featured in "Numerical Recipes in C"
	 * by Press et al.
	 * This allows for cache-friendly matrices with arbitrary non-zero indexing.
	 */
	double* onesVector;
	double* outputVector;
	double** hilbertMatrix;
	onesVector = vector(1, N);
	outputVector = vector(1, N);
	hilbertMatrix = matrix(1, N, 1, N);

	/* Define indices and matrix elements. */
	long row, col;
	for (row = 1; row <= N; ++row) {
		onesVector[row] = 1.0;
	}

	for (row = 1; row <= N; ++row) {
		for (col = 1; col <= N; ++col) {
			hilbertMatrix[row][col] = 1.0 / (double) (row + col - 1);
		}
	}

	/* Print Hilbert Matrix. */
	printf("%dx%d Hilbert Matrix:\n", N, N);
	for (row = 1; row <= N; ++row) {
		for (col = 1; col <= N; ++col) {
			printf("%f ",hilbertMatrix[row][col]);
		}
		printf("\n");
	}
	printf("\n");
	
	/* Perform calculation and print resultant vector. */
	printf("Result of multiplying by ones vector:\n");
	for (row = 1; row <= N; ++row) {
		for (col = 1; col <= N; ++col) {
			outputVector[row] += hilbertMatrix[row][col] * onesVector[col];
		}
	}

	for (row = 1; row <= N; ++row) {
		printf("%f\n", outputVector[row]);
	}

	return 0;
}

/* src/hilbert_multiply.c */

