/* src/include/linalg_util.h */
#ifndef _LINALG_UTIL_H_
#define _LINALG_UTIL_H_

static double sqrarg;
#define SQR(a) ((sqrarg=(a)) == 0.0 ? 0.0 : sqrarg * sqrarg)

static float fsqrarg;
#define FSQR(a) ((fsqrarg=(a)) == 0.0 ? 0.0 : fsqrarg * fsqrarg)

static double dmaxarg1, dmaxarg2;
#define DMAX(a,b) (dmaxarg1 = (a), dmaxarg2 = (b), (dmaxarg1) > (dmaxarg2) ?\
		(dmaxarg1) : (dmaxarg2))

static double dminarg1, dminarg2;
#define DMIN(a,b) (dminarg1 = (a), dminarg2 = (b), (dminarg1) < (dminarg2) ?\
		(dminarg1) : (dminarg2))

static float fmaxarg1, fmaxarg2;
#define FMAX(a,b) (fmaxarg1 = (a), fmaxarg2 = (b), (fmaxarg1) > (fmaxarg2) ?\
		(fmaxarg1) : (fmaxarg2))

static float fminarg1, fminarg2;
#define FMIN(a,b) (fminarg1 = (a), fminarg2 = (b), (fminarg1) > (fminarg2) ?\
		(fminarg1) : (fminarg2))

void printError(char errorMsg[]);

double* vector(long low, long high);
double* fvector(long low, long high);
double** matrix(long lowRow, long highRow, long lowCol, long highCol);
double** fmatrix(long lowRow, long highRow, long lowCol, long highCol);
double** submatrix(double** a, long oldLowRow, long oldHighRow, long oldLowCol, long oldHighCol,
		long newLowRow, long newLowCol);
double** convert_matrix(double* a, long lowRow, long highRow, long lowCol, long highCol);

void free_vector(double* v, long low, long high);
void free_fvector(float* v, long low, long high);
void free_matrix(double** m, long lowRow, long highRow, long lowCol, long highCol);
void free_fmatrix(float** m, long lowRow, long highRow, long lowCol, long highCol);
void free_submatrix(double** b, long lowRow, long highRow, long lowCol, long highCol);
void free_convert_matrix(double** b, long lowRow, long highRow, long lowCol, long highCol); 

#endif
/* src/include/linalg_util.h */

