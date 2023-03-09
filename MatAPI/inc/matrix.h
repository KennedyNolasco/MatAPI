/* ADT Matrix */

#ifndef _MATRIX_H
#define _MATRIX_H

typedef struct Matrix {
	char nome[128];
	unsigned int nlins;
	unsigned int ncols;
	double      *values;
} Matrix;

extern Matrix matrix_nul;
Matrix matrix_value_init(unsigned int nlins, unsigned int ncols, double value,char* nome) ;
Matrix matrix_zeros(unsigned int nlins, unsigned int ncols,char* nome);
Matrix matrix_ones(unsigned int nlins, unsigned int ncols,char* nome);
Matrix matrix_identity(unsigned int nlins, unsigned int ncols,char* nome);
Matrix matrix_copy(Matrix m);
Matrix matrix_apply(double (*f)(double val), Matrix m);

void matrix_free(Matrix *m);

double       matrix_value(Matrix m, int i, int j);
unsigned int matrix_nlins(Matrix m);
unsigned int matrix_ncols(Matrix m);

void matrix_rename(Matrix* A, char* nome);
Matrix matrix_paste(Matrix A,double arr[]);
Matrix matrix_mmul(Matrix A, Matrix B);
Matrix matrix_madd(Matrix A, Matrix B);
Matrix matrix_msub(Matrix A, Matrix B);
Matrix matrix_smul(Matrix A, double scalar);
Matrix matrix_sadd(Matrix A, double scalar);
Matrix matrix_ssub(Matrix A, double scalar);
Matrix matrix_transpose(Matrix A);
double det(Matrix A);
Matrix matrix_inverse2(Matrix A);
void print_matrix(const char *const name, const Matrix m);
#endif
