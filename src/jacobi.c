/* src/jacobi.c */

#include <math.h>
#include <stdio.h>
#include "linalg_util.h"

const long GRID_W = 33;
const long GRID_H = 33;
const double STEP = 2.0 / 33.0;
const long ITER = 10;
const double xMin = -1.0;
const double xMax = 1.0;
const double yMin = -1.0;
const double yMax = 1.0;

int main() {
	double** sourceMatrix;
	sourceMatrix = matrix(1, GRID_W, 1, GRID_H);

	long row, col;
	double xPos, yPos;
	for (row = 1; row <= GRID_W; ++row) {
		for (col = 1; col <= GRID_H; ++col) {
			xPos = fabs(xMin + (row * STEP));
			yPos = fabs(yMin + (col * STEP));
			if (xPos < 0.5 && yPos < 0.5) {
				sourceMatrix[row][col] = 1.0;
			}
			else {
				sourceMatrix[row][col] = 0.0;
			}
		}
	}
	
	for (row = 1; row <= GRID_W; ++row) {
		for (col = 1; col <= GRID_H; ++col) {
			if (row == GRID_W) {
				printf("%f", sourceMatrix[row][col]);
			}
			else {
				printf("%f,", sourceMatrix[row][col]);
			}
		}
		printf("\n");
	}
	printf("\n");

	return 0;
}

/* src/jacobi.c */

