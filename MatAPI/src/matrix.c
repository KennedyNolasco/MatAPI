/*
	Implementação da ADT Matrix
*/

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "matrix.h"
Matrix matrix_nul = {.nome="NULL",.nlins=0, .ncols=0, .values=NULL};

#define VALUES(m, i, j) (m.values[i * m.ncols + j])

double matrix_value(Matrix m, int i, int j) {
	return VALUES(m, i, j);
}

Matrix matrix_value_init(unsigned int nlins, unsigned int ncols, double value,char* nome) {
	Matrix m = matrix_nul;
	strcpy(m.nome,nome);
	m.values = malloc(nlins * ncols * sizeof(double));
	if(m.values) {
		m.nlins = nlins;
		m.ncols = ncols;
		for(int i=0; i<nlins; i++)
			for(int j=0; j<ncols; j++)
				VALUES(m, i, j) = value;
	}
	return m;
}

Matrix matrix_zeros(unsigned int nlins, unsigned int ncols, char* nome) {
	return matrix_value_init(nlins, ncols, 0.0,nome);
}

Matrix matrix_ones(unsigned int nlins, unsigned int ncols, char* nome) {
	return matrix_value_init(nlins, ncols, 1.0,nome);
}

Matrix matrix_identity(unsigned int nlins, unsigned int ncols,char* nome) {
	Matrix m = matrix_nul;
	strcpy(m.nome,nome);
	m.values = malloc(nlins * ncols * sizeof(double));
	if(m.values) {
		m.nlins = nlins;
		m.ncols = ncols;
		for(int i=0; i<nlins; i++)
			for(int j=0; j<ncols; j++)
				m.values[i*ncols + j] = (i == j) ? 1.0 : 0.0;
	}
	return m;
}

void matrix_free(Matrix *m) {
	if(m) {
		free(m->values);
		*m = matrix_nul;
	}
}

double matrix_getValue(Matrix m, int i, int j) {
	if(i >= m.nlins || j >= m.ncols)
		return NAN;
	return m.values[i*m.ncols + j];
}

unsigned int matrix_nlins(Matrix m) {
	return m.nlins;
}

unsigned int matrix_ncols(Matrix m) {
	return m.ncols;
}

Matrix matrix_copy(Matrix m) { //incompleta ainda
	Matrix res;
	res.nlins = m.nlins;
	res.ncols = m.ncols;
	m.values = calloc(res.nlins * res.ncols, sizeof(double));
	if(m.values) {
		for(int i=0; i < res.nlins; i++)
			for(int j=0; j < res.ncols; j++)
				VALUES(res, i, j) = VALUES(m, i, j);
		return m;
	}
	else
		return matrix_nul;
}

Matrix matrix_apply(double (*f)(double val), Matrix m) {//incompleta ainda
	Matrix res;
	res.nlins = m.nlins;
	res.ncols = m.ncols;
	res.values = calloc(m.nlins * m.ncols, sizeof(double));
	if(m.values) {
		for(int i=0; i < res.nlins; i++)
			for(int j=0; j < res.ncols; j++)
				VALUES(res,i,j) = f(VALUES(m,i,j));
		return res;
	}
	else
		return matrix_nul;
}


Matrix matrix_mmul(Matrix A, Matrix B){ //operação A*B
	if(A.ncols!=B.nlins){
		printf("Erro de dimensão de matriz!\n");
		return matrix_nul;
	}
	else{
	Matrix C = matrix_value_init(A.nlins, B.ncols, 60.0,strcat(A.nome,B.nome));	
	for(int i=0; i<A.nlins; i++){
			for(int j=0; j<B.ncols; j++){
				VALUES(C,i,j) = 0;
				for(int k=0;k<B.nlins;k++){
					VALUES(C,i,j) += VALUES(A,i,k)*VALUES(B,k,j);	
				}
			}
	}
	return C;
	}
	
}
Matrix matrix_madd(Matrix A, Matrix B){ //operação: A + B
	if(A.nlins!=B.nlins || A.ncols!=B.ncols){
		printf("Erro de dimensão de matriz!\n");
		return matrix_nul;
	}
	Matrix C = matrix_value_init(A.nlins, A.ncols, 0.0,strcat(A.nome,B.nome));
	for(int i=0; i<A.nlins; i++){
			for(int j=0; j<A.ncols; j++){
				VALUES(C, i, j) = VALUES(A,i,j)+VALUES(B,i,j);
			}
	}
	return C;
}
Matrix matrix_msub(Matrix A, Matrix B){ // operação: A-B
	if(A.nlins!=B.nlins || A.ncols!=B.ncols){
		printf("Erro de dimensão de matriz!\n");
		return matrix_nul;
	}
	Matrix C = matrix_value_init(A.nlins, A.ncols, 0.0,strcat(A.nome,B.nome));
	for(int i=0; i<A.nlins; i++){
			for(int j=0; j<A.ncols; j++){
				VALUES(C, i, j) = VALUES(A,i,j)-VALUES(B,i,j);
			}
	}
	return C;
}
Matrix matrix_smul(Matrix A, double scalar){// operação x*A
	char str[128];
	sprintf(str,"%lf",scalar);
	Matrix C = matrix_value_init(A.nlins, A.ncols, 0.0,strcat(strcat(A.nome,"times"),str));
	for(int i=0; i<A.nlins; i++){
			for(int j=0; j<A.ncols; j++){
				VALUES(C, i, j) = VALUES(A,i,j)*scalar;
			}
	}
	return C;
}
Matrix matrix_sadd(Matrix A, double scalar){// operação x+A
	char str[128];
	sprintf(str,"%lf",scalar);
	Matrix C = matrix_value_init(A.nlins, A.ncols, 0.0,strcat(strcat(A.nome,"add"),str));
	for(int i=0; i<A.nlins; i++){
			for(int j=0; j<A.ncols; j++){
				VALUES(C, i, j) = VALUES(A,i,j)+scalar;
			}
	}
	return C;
}
Matrix matrix_ssub(Matrix A, double scalar){// operação x-A
	char str[128];
	sprintf(str,"%lf",scalar);
	Matrix C = matrix_value_init(A.nlins, A.ncols, 0.0,strcat(strcat(A.nome,"sub"),str));
	for(int i=0; i<A.nlins; i++){
			for(int j=0; j<A.ncols; j++){
				VALUES(C, i, j) = VALUES(A,i,j)-scalar;
			}
	}
	return C;
}
Matrix matrix_transpose(Matrix A){
	Matrix C = matrix_value_init(A.ncols, A.nlins, 0.0,strcat(A.nome,"transposed"));
	for(int i=0;i<A.ncols;i++){
		for(int j=0;j<A.nlins;j++){
			VALUES(C, i, j) = VALUES(A, j, i);
		}
	}
	return C;
}
double det(Matrix A) {
    int linhasA = A.nlins;
    int colunasA = A.ncols;
    if (linhasA != colunasA) {
        printf("Erro de dimensão de matriz!\n");
        return -1;
    }
    else if (linhasA == 1)
        return (VALUES(A,0,0));
    else if (linhasA == 2)
        return (VALUES(A,0,0)*VALUES(A,1,1) - VALUES(A,1,0)*VALUES(A,0,1));
    else {
        Matrix menor = matrix_value_init(A.nlins-1, A.ncols-1, 0.0,A.nome);
        int linmenor, colmenor;
        int indicecol_primeiralin;
        double sum = 0;
        register int poslinha,poscoluna;
        for(indicecol_primeiralin = 0; indicecol_primeiralin < linhasA;
                indicecol_primeiralin++) {
            linmenor = 0;
            for(poslinha = 1; poslinha < linhasA; poslinha++) {
                colmenor = 0;
                for(poscoluna = 0; poscoluna < colunasA; poscoluna++) {
                    if (poscoluna == indicecol_primeiralin)
                        continue;
                    else
                        VALUES(menor,linmenor,colmenor) = VALUES(A,poslinha,poscoluna);
                    colmenor++;
                }
                linmenor++;
            }
            //m = linmenor;
            //n = colmenor;
            if (indicecol_primeiralin % 2 == 0)
                sum += (VALUES(A,0,indicecol_primeiralin)* det(menor));
            else
                sum -= (VALUES(A,0,indicecol_primeiralin) * det(menor));
        }
	matrix_free(&menor);
        return sum;
    }
}     
Matrix matrix_paste(Matrix A,double arr[]){
	int i=0;
	int linha=0;
	int coluna=0;
	for(i=0;i<(A.nlins*A.ncols);i++){
		VALUES(A,linha,coluna) = arr[i];
		coluna++;
		if(i+1%A.ncols==0){
			linha++;
			coluna=0;
		}
		
		
	}
	return A;
}
void matrix_rename(Matrix* A, char* nome){
	strcpy(A->nome,nome);;
}    
Matrix matrix_inverse2(Matrix A){
   if(det(A)==0){
   	printf("Determinante da matriz é zero, não existe inversa!\n");
        return matrix_nul;
   }
   else if(A.nlins!=A.ncols){
	printf("Número de linhas deve ser igual ao número de colunas!\n");
        return matrix_nul;
   }
   else{
        if(A.nlins==1||A.ncols==1){
            Matrix D = matrix_value_init(A.nlins,A.ncols,1/VALUES(A,0,0),"matriz D");
	    return D;
        }
        else{
            int p, q, m, n, i, j;
            Matrix B = matrix_value_init(A.nlins-1,A.ncols-1,1,"matriz B");
            Matrix C = matrix_value_init(A.nlins,A.ncols,1,"matriz C");
            for (q = 0;q < A.nlins; q++){
                for (p = 0;p < A.nlins; p++){
                        m = 0;
                        n = 0;
                        for (i = 0;i <  A.nlins; i++){
                            for (j = 0;j <  A.nlins; j++){
                            if (i != q && j != p){
                                VALUES(B,m,n) = VALUES(A,i,j);
                                if (n < ( A.nlins - 2))
                                n++;
                                else{
                                n = 0;
                                m++;
                                }
                            }
                            }
                        }
                    int pp=-1;
                    if((q+p)%2==0){
                        pp= 1;
                    }
                    VALUES(C,q,p) = pp * det(B);
                    }
            }
            Matrix Q = matrix_transpose(C);
            for (i = 0;i < A.nlins; i++) {
                for (j = 0;j < A.nlins; j++){
                    VALUES(C,i,j) = VALUES(Q,i,j) / det(A);
                }
            }
            matrix_free(&Q);
            matrix_free(&B);
	    return C;
        }
    }
}
void print_matrix(const char *const name, const Matrix m) {
	printf("%s(%u,%u) = [\n", name, m.nlins, m.ncols);
	for(int i = 0; i < matrix_nlins(m); i++) {
		printf("\t[%4.4f", matrix_value(m, i, 0));
		for(int j = 1; j < matrix_ncols(m); j++) {
			printf(", %4.4f", matrix_value(m, i, j));
		}
		puts("]");
	}
	puts("]");
}