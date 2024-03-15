/* src/include/linalg_util.c */
#ifndef _LINALG_UTIL_
#define _LINALG_UTIL_

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#define VEC_END 1

void printError(char errorMsg[]) {
	fprintf(stderr, "Lin. Alg. Util. runtime error:\n");
	fprintf(stderr, "%s\n", errorMsg);
	fprintf(stderr, "...exiting to system.\n");
	exit(1);
}

double* vector(long low, long high) {
	double* v;
	v = (double *) malloc( (size_t) ((high - low + 1 + VEC_END) * sizeof(double)) );
	if (!v) printError("Allocation failure in vector()");
	return v - low + VEC_END;
}

float* fvector(long low, long high) {
	float* v;
	v = (float *) malloc( (size_t) ((high - low + 1 + VEC_END) * sizeof(float)) );
	if (!v) printError("Allocation failure in fvector()");
	return v - low + VEC_END;
}

double** matrix(long lowRow, long highRow, long lowCol, long highCol) {
	long numRow = highRow - lowRow + 1;
	long numCol = highCol - lowCol + 1;

	double** m;
	m = (double **) malloc( (size_t) ((numRow + VEC_END) * sizeof(double*)) );
	if (!m) printError("Row allocation failure in matrix()");
	m += VEC_END;
	m -= lowRow;

	m[lowRow] = (double *) malloc( (size_t) ((numRow * numCol + VEC_END) * sizeof(double)) );
	if (!m) printError("Column allocation failure in matrix()");
	m[lowRow] += VEC_END;
	m[lowRow] -= lowCol;

	for (long i = lowRow + 1; i <= highRow; ++i) {
		m[i] = m[i-1] + numCol;
	}
	return m;
}

float** fmatrix(long lowRow, long highRow, long lowCol, long highCol) {
	long numRow = highRow - lowRow + 1;
	long numCol = highCol - lowCol + 1;

	float** m;
	m = (float **) malloc( (size_t) ((numRow + VEC_END) * sizeof(float*)) );
	if (!m) printError("Row allocation failure in fmatrix()");
	m += VEC_END;
	m -= lowRow;

	m[lowRow] = (float *) malloc( (size_t) ((numRow * numCol + VEC_END) * sizeof(float)) );
	if (!m) printError("Column allocation failure in fmatrix()");
	m[lowRow] += VEC_END;
	m[lowRow] -= lowCol;

	for (long i = lowRow + 1; i <= highRow; ++i) {
		m[i] = m[i-1] + numCol;
	}
	return m;
}

double** submatrix(double** a, long oldLowRow, long oldHighRow, long oldLowCol, long oldHighCol,
		long newLowRow, long newLowCol) {
	long numRow = oldHighRow - oldLowRow + 1;
	long numCol = oldLowCol - newLowCol + 1;

	double** m;
	m = (double **) malloc( (size_t) ((numRow + VEC_END) * sizeof(double*)) );
	if (!m) printError("Allocation failure in submatrix()");
	m += VEC_END;
	m -= newLowRow;

	for (long i = oldLowRow, j = newLowRow; i <= oldHighRow; ++i, ++j) {
		m[j] = a[i] + numCol;
	}
	return m;
}
double** convert_matrix(double* a, long lowRow, long highRow, long lowCol, long highCol) {
	long numRow = highRow - lowRow + 1;
	long numCol = highCol - lowCol + 1;

	double** m;
	m = (double **) malloc( (size_t) ((numRow + VEC_END) * sizeof(double*)) );
	if (!m) printError("Allocation failure in convert_matrix()");
	m += VEC_END;
	m -= lowRow;

	m[lowRow] = a - lowCol;
	for (long i = 1, j = lowRow + 1; i < numRow; ++i, ++j) {
		m[j] = m[j-1] + numCol;
	}
	return m;
}

void free_vector(double* v, long low, long high) {
	free((char*) (v + low - VEC_END));
}

void free_fvector(float* v, long low, long high) {
	free((char*) (v + low - VEC_END));
}

void free_matrix(double** m, long lowRow, long highRow, long lowCol, long highCol) {
	free((char*) (m[lowRow] + lowCol - VEC_END));
	free((char*) (m + lowRow - VEC_END));
}

void free_fmatrix(float** m, long lowRow, long highRow, long lowCol, long highCol) {
	free((char*) (m[lowRow] + lowCol - VEC_END));
	free((char*) (m + lowRow - VEC_END));
}

void free_submatrix(double** b, long lowRow, long highRow, long lowCol, long highCol) {
	free((char*) (b + lowRow - VEC_END));
}

void free_convert_matrix(double** b, long lowRow, long highRow, long lowCol, long highCol) {
	free((char*) (b + lowRow - VEC_END));
}

#endif
/* src/include/linalg_util.c */

