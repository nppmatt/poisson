/* src/jacobi.c */

#include <math.h>
#include <stdio.h>
#include "linalg_util.h"

const long GRID_W = 33;
const long GRID_H = 33;
const long ITER = 10;
const double xMin = -1.0;
const double xMax = 1.0;
const double yMin = -1.0;
const double yMax = 1.0;
const double dx = (xMax - xMin) / (GRID_W - 1);
const double dy = (yMax - yMin) / (GRID_H - 1);
const double dxxinv = 1.0 / (dx * dx);
const double dyyinv = 1.0 / (dy * dy);
const double dmid = 1.0 / (2.0 * (dxxinv + dyyinv));

/* Source function given an the row and column indices.
 * (Mind that steps are hardcoded for square domains.)
 * Ternary statement taken from Rycroft's header.
 */
inline double srcFunc(long i, long j) {
	double x = xMin + i * dx;
	double y = yMin + j * dy;
	return fabs(x) > 0.5 || fabs(y) > 0.5 ?0:1;
}

/* 2-D Jacobi approximate given a guess as input. */
double** jacobi(double** input, long iterations) {
	double** approx;
	double** swap;
	approx = matrix(1, GRID_W, 1, GRID_H);
	swap = matrix(1, GRID_W, 1, GRID_H);
	long it, row, col;
	for (it = 1; it <= iterations; ++it) {
		if (it % 2 == 0) {
			swap = input;
			input = approx;
			approx = input;
		}
		for (row = 2; row <= GRID_H-1; ++row) {
			for (col = 2; col <= GRID_W-1; ++col) {
				approx[row][col] = (srcFunc(row, col) + 
					dxxinv * (approx[row][col+1] + approx[row][col-1]) +
					dyyinv * (approx[row+1][col] + approx[row-1][col])
					) * dmid;
			}
		}
	}
	return approx;
}

int main() {
	double** guess;
	double** approxOutput;
	guess = matrix(1, GRID_W, 1, GRID_H);
	approxOutput = matrix(1, GRID_W, 1, GRID_H);

	long row, col;
	double xPos, yPos;

	/* Set source function over grid */
	for (row = 1; row <= GRID_H; ++row) {
		for (col = 1; col <= GRID_W; ++col) {
			guess[row][col] = 0.0;
		}
	}

	approxOutput = jacobi(guess, 10);


	/* Print data as CSV with last row to be truncated */
	for (row = 1; row <= GRID_H; ++row) {
		for (col = 1; col <= GRID_W; ++col) {
			if (col == GRID_W) {
				printf("%f", approxOutput[row][col]);
			}
			else {
				printf("%f,", approxOutput[row][col]);
			}
		}
		printf("\n");
	}
	printf("\n");

	return 0;
}

/* src/jacobi.c */

