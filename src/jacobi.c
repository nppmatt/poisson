/* src/jacobi.c */

#include <math.h>
#include <stdio.h>
#include "linalg_util.h"

const long GRID_W = 33;
const long GRID_H = 33;
const double STEP = 1.0 / GRID_W;
const long ITER = 10;
const double xMin = -1.0;
const double xMax = 1.0;
const double yMin = -1.0;
const double yMax = 1.0;

/* Source function given an the row and column indices.
 * (Mind that steps are hardcoded for square domains.)
 * Ternary statement taken from Rycroft's header.
 */
inline double srcFunc(long i, long j) {
	double x = xMin + i * STEP;
	double y = yMin + j * STEP;
	return (fabs(x) > 0.5 || fabs(y) > 0.5)?0:1;
}

/* 2-D Jacobi approximate given the current state of a grid. */
void jacobi(double** approx, long iterations) {
	long it, row, col;
	for (it = 0; it < iterations; ++it) {
		for (row = 2; row <= GRID_H-1; ++row) {
			for (col = 2; col <= GRID_W-1; ++col) {
				approx[row][col] = (STEP*STEP*srcFunc(row, col) + 
						approx[row][col+1] + approx[row][col-1] +
						approx[row+1][col] + approx[row-1][col]) / 
						4.0;
			}
		}
	}
}

int main() {
	double** approxMatrix;
	approxMatrix = matrix(1, GRID_W, 1, GRID_H);

	long row, col;
	double xPos, yPos;

	/* Set source function over grid */
	for (row = 1; row <= GRID_H; ++row) {
		for (col = 1; col <= GRID_W; ++col) {
			approxMatrix[row][col] = 0.0;
		}
	}

	jacobi(approxMatrix, 10);


	/* Print data as CSV with last row to be truncated */
	for (row = 1; row <= GRID_H; ++row) {
		for (col = 1; col <= GRID_W; ++col) {
			if (col == GRID_W) {
				printf("%f", approxMatrix[row][col]);
			}
			else {
				printf("%f,", approxMatrix[row][col]);
			}
		}
		printf("\n");
	}
	printf("\n");

	return 0;
}

/* src/jacobi.c */

