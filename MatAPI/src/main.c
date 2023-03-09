#define VALUES(m, i, j) (m.values[i * m.ncols + j])
#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include <string.h>
#include "integral.h"
double func(double x){
    return x*x;
}
double funcIntegrada(double x){ 
	return (x*x*x)/3;
}
int main(int argc, char **argv) { //SETA O LONGJMP E SETJMP ?
	double arr[1024];
	Matrix vetorMatriz[1024];
	Integral integral;
	integral.a=0;
	integral.b=0;
	integral.func = *func;
	int i;
	for(i=0;i<1023;i++){
		vetorMatriz[i] = matrix_nul;
	}
	int op=-1;
	int op2=-1;
	int linmatriz =0;
	int colmatriz =0;
	int numMatriz=0;
	int matrizA=-1;
	int matrizB=-1;
	double determinante=0;
	double scalar=0;
	char nomeMatriz[128];
	int a=0;
	double integralResult=0;
	char nomeMatriz2[128];
	if(a){};
	while(op!=7){
		printf("Selecione operação:\n 1 - Adicionar Matriz \n 2 - Operações de matriz com matriz \n 3 - Operações de matriz com escalar \n 4 - Operações de matrizes\n 5 - Printar todas as matrizes existentes\n 6 - Integrar função func definida\n 7 - Sair\n");
		a = scanf("%d",&op);
		switch(op){
			case 1:
				printf("Digite o número de linhas, colunas, e nome da Matriz:\n");
				a=scanf("%d",&linmatriz);
				a=scanf("%d",&colmatriz);
				a=scanf("%s",nomeMatriz);
				while(linmatriz<=0  || colmatriz<=0){
					printf("Número de linhas e colunas deve ser maior que 0\n");
					printf("Digite o número de linhas e colunas:\n");
					a=scanf("%d",&linmatriz);
					a=scanf("%d",&colmatriz);
				}
				i=0;
				while(i<numMatriz){
					if(strcmp(vetorMatriz[i].nome,nomeMatriz)==0){
						printf("Nome de matriz já existe, escolha outro nome\n");
						a=scanf("%s",nomeMatriz);
						i=-1;
					}
					i++;
				}
				i=0;
				vetorMatriz[numMatriz] = matrix_identity(linmatriz,colmatriz,nomeMatriz);
				printf("Digite os elementos da matriz:\n");
				for(i=0;i<linmatriz*colmatriz;i++){
					a=scanf("%lf",&arr[i]);
				}
				vetorMatriz[numMatriz] = matrix_paste(vetorMatriz[numMatriz],arr);
				numMatriz++;
				printf("Matriz adicionada:\n");
				print_matrix(vetorMatriz[numMatriz-1].nome,vetorMatriz[numMatriz-1]);
				break;
			case 2:
				printf("Selecione qual operação:\n 1 - Multiplicação de duas matrizes \n 2 - Soma de duas matrizes \n 3 - Subtração de duas matrizes\n");
				a=scanf("%d",&op2);
				switch(op2){
					case 1:
						printf("Qual o nome das duas matrizes a serem multiplicadas?\n");
						a=scanf("%s",nomeMatriz);
						a=scanf("%s",nomeMatriz2);
						for(i=0;i<numMatriz;i++){
							if(strcmp(vetorMatriz[i].nome,nomeMatriz)==0){	
								matrizA = i;
							}
							if(strcmp(vetorMatriz[i].nome,nomeMatriz2)==0){
								matrizB = i;
							}
						}
						if(matrizA==-1 || matrizB==-1){
							printf("Matriz não existente\n\n");
						}
						else{
							if(vetorMatriz[matrizA].ncols!=vetorMatriz[matrizB].nlins){
								printf("Erro de dimensão de matriz!\n");
							}
							else{
							vetorMatriz[numMatriz] = matrix_mmul(vetorMatriz[matrizA],vetorMatriz[matrizB]);
							printf("Qual o nome da matriz resultante?\n");
							a=scanf("%s",nomeMatriz);
							i=0;
							while(i<numMatriz){
								if(strcmp(vetorMatriz[i].nome,nomeMatriz)==0){
									printf("Nome de matriz já existe, escolha outro nome\n");
									a=scanf("%s",nomeMatriz);
									i=-1;
								}
								i++;
							}
							i=0;
							matrix_rename(&vetorMatriz[numMatriz],nomeMatriz);
							printf("Matrizes a serem multiplicadas:\n");
							print_matrix(vetorMatriz[matrizA].nome,vetorMatriz[matrizA]);
							print_matrix(vetorMatriz[matrizB].nome,vetorMatriz[matrizB]);
							printf("Resultado da multiplicação:\n");
							print_matrix(vetorMatriz[numMatriz].nome,vetorMatriz[numMatriz]);
							numMatriz++;
							}
						}
						matrizA=-1;
						matrizB=-1;
						break;
					case 2:
						printf("Qual o nome das duas matrizes a serem somadas?\n");
						a=scanf("%s",nomeMatriz);
						a=scanf("%s",nomeMatriz2);
						for(i=0;i<numMatriz;i++){
							if(strcmp(vetorMatriz[i].nome,nomeMatriz)==0){	
								matrizA = i;
							}
							if(strcmp(vetorMatriz[i].nome,nomeMatriz2)==0){
								matrizB = i;
							}
						}
						if(matrizA==-1 || matrizB==-1){
							printf("Matriz não existente\n\n");
						}
						else{
							if(vetorMatriz[matrizA].nlins!=vetorMatriz[matrizB].nlins|| vetorMatriz[matrizA].ncols!=vetorMatriz[matrizB].ncols){
								printf("Erro de dimensão de matriz!\n");
							}
							else{
							vetorMatriz[numMatriz] = matrix_madd(vetorMatriz[matrizA],vetorMatriz[matrizB]);
							printf("Qual o nome da matriz resultante?\n");
							a=scanf("%s",nomeMatriz);
							i=0;
							while(i<numMatriz){
								if(strcmp(vetorMatriz[i].nome,nomeMatriz)==0){
									printf("Nome de matriz já existe, escolha outro nome\n");
									a=scanf("%s",nomeMatriz);
									i=-1;
								}
								i++;
							}
							i=0;
							matrix_rename(&vetorMatriz[numMatriz],nomeMatriz);
							printf("Matrizes a serem somadas:\n");
							print_matrix(vetorMatriz[matrizA].nome,vetorMatriz[matrizA]);
							print_matrix(vetorMatriz[matrizB].nome,vetorMatriz[matrizB]);
							printf("Resultado da soma:\n");
							print_matrix(vetorMatriz[numMatriz].nome,vetorMatriz[numMatriz]);
							numMatriz++;
							}
						}
						matrizA=-1;
						matrizB=-1;
						break;
					case 3:
						printf("Qual o nome das duas matrizes a serem subtraídas?\n");
						a=scanf("%s",nomeMatriz);
						a=scanf("%s",nomeMatriz2);
						for(i=0;i<numMatriz;i++){
							if(strcmp(vetorMatriz[i].nome,nomeMatriz)==0){	
								matrizA = i;
							}
							if(strcmp(vetorMatriz[i].nome,nomeMatriz2)==0){
								matrizB = i;
							}
						}
						if(matrizA==-1 || matrizB==-1){
							printf("Matriz não existente\n\n");
						}
						else{
							if(vetorMatriz[matrizA].nlins!=vetorMatriz[matrizB].nlins|| vetorMatriz[matrizA].ncols!=vetorMatriz[matrizB].ncols){
								printf("Erro de dimensão de matriz!\n");
							}
							else{
							vetorMatriz[numMatriz] = matrix_msub(vetorMatriz[matrizA],vetorMatriz[matrizB]);
							printf("Qual o nome da matriz resultante?\n");
							a=scanf("%s",nomeMatriz);
							i=0;
							while(i<numMatriz){
								if(strcmp(vetorMatriz[i].nome,nomeMatriz)==0){
									printf("Nome de matriz já existe, escolha outro nome\n");
									a=scanf("%s",nomeMatriz);
									i=-1;
								}
								i++;
							}
							i=0;
							matrix_rename(&vetorMatriz[numMatriz],nomeMatriz);
							printf("Matrizes a serem subtraídas:\n");
							print_matrix(vetorMatriz[matrizA].nome,vetorMatriz[matrizA]);
							print_matrix(vetorMatriz[matrizB].nome,vetorMatriz[matrizB]);
							printf("Resultado da subtração:\n");
							print_matrix(vetorMatriz[numMatriz].nome,vetorMatriz[numMatriz]);
							numMatriz++;
							}
						}
						matrizA=-1;
						matrizB=-1;
						break;
					default:
						printf("Operação inválida\n");
				}
				break;
			case 3:
				printf("Selecione qual operação:\n 1 - Multiplicação de matriz por escalar \n 2 - Soma de matriz por escalar  \n 3 - Subtração de matriz por escalar\n");
				a=scanf("%d",&op2);
				switch(op2){
					case 1:
						printf("Multiplicação por escalar: Qual o nome da matriz e o escalar?\n");
						a=scanf("%s",nomeMatriz);
						a=scanf("%lf",&scalar);
						for(i=0;i<numMatriz;i++){
							if(strcmp(vetorMatriz[i].nome,nomeMatriz)==0){	
								matrizA = i;
							}
						}
						if(matrizA==-1){
							printf("Matriz não existente\n\n");
						}
						else{
							vetorMatriz[numMatriz] = matrix_smul(vetorMatriz[matrizA],scalar);
							printf("Qual o nome da matriz resultante?\n");
							a=scanf("%s",nomeMatriz);
							i=0;
							while(i<numMatriz){
								if(strcmp(vetorMatriz[i].nome,nomeMatriz)==0){
									printf("Nome de matriz já existe, escolha outro nome\n");
									a=scanf("%s",nomeMatriz);
									i=-1;
								}
								i++;
							}
							i=0;
							matrix_rename(&vetorMatriz[numMatriz],nomeMatriz);
							printf("Matriz a ser multiplicada por %lf:\n",scalar);
							print_matrix(vetorMatriz[matrizA].nome,vetorMatriz[matrizA]);
							printf("Resultado da multiplicação:\n");
							print_matrix(vetorMatriz[numMatriz].nome,vetorMatriz[numMatriz]);
							numMatriz++;
						}
						matrizA=-1;
						break;
					case 2:
						printf("Soma por escalar: Qual o nome da matriz e o escalar?\n");
						a=scanf("%s",nomeMatriz);
						a=scanf("%lf",&scalar);
						for(i=0;i<numMatriz;i++){
							if(strcmp(vetorMatriz[i].nome,nomeMatriz)==0){	
								matrizA = i;
							}
						}
						if(matrizA==-1){
							printf("Matriz não existente\n\n");
						}
						else{
							vetorMatriz[numMatriz] = matrix_sadd(vetorMatriz[matrizA],scalar);
							printf("Qual o nome da matriz resultante?\n");
							a=scanf("%s",nomeMatriz);
							i=0;
							while(i<numMatriz){
								if(strcmp(vetorMatriz[i].nome,nomeMatriz)==0){
									printf("Nome de matriz já existe, escolha outro nome\n");
									a=scanf("%s",nomeMatriz);
									i=-1;
								}
								i++;
							}
							i=0;
							matrix_rename(&vetorMatriz[numMatriz],nomeMatriz);
							printf("Matriz a ser somada por %lf:\n",scalar);
							print_matrix(vetorMatriz[matrizA].nome,vetorMatriz[matrizA]);
							printf("Resultado da soma:\n");
							print_matrix(vetorMatriz[numMatriz].nome,vetorMatriz[numMatriz]);
							numMatriz++;
						}
						matrizA=-1;
						break;
					case 3:
						printf("Subtração por escalar: Qual o nome da matriz e o escalar?\n");
						a=scanf("%s",nomeMatriz);
						a=scanf("%lf",&scalar);
						for(i=0;i<numMatriz;i++){
							if(strcmp(vetorMatriz[i].nome,nomeMatriz)==0){	
								matrizA = i;
							}
						}
						if(matrizA==-1){
							printf("Matriz não existente\n\n");
						}
						else{
							vetorMatriz[numMatriz] = matrix_ssub(vetorMatriz[matrizA],scalar);
							printf("Qual o nome da matriz resultante?\n");
							a=scanf("%s",nomeMatriz);
							i=0;
							while(i<numMatriz){
								if(strcmp(vetorMatriz[i].nome,nomeMatriz)==0){
									printf("Nome de matriz já existe, escolha outro nome\n");
									a=scanf("%s",nomeMatriz);
									i=-1;
								}
								i++;
							}
							i=0;
							matrix_rename(&vetorMatriz[numMatriz],nomeMatriz);
							printf("Matriz a ser subtraída por %lf:\n",scalar);
							print_matrix(vetorMatriz[matrizA].nome,vetorMatriz[matrizA]);
							printf("Resultado da subtração:\n");
							print_matrix(vetorMatriz[numMatriz].nome,vetorMatriz[numMatriz]);
							numMatriz++;
						}
						matrizA=-1;
						break;
					default:
						printf("Operação inválida\n");
				}
				break;
			case 4:
				printf("Selecione qual operação:\n 1 - Achar transposta de uma matriz \n 2 - Achar determinante de uma matriz  \n 3 - Achar matriz inversa\n");
				a=scanf("%d",&op2);
				switch(op2){
					case 1:
						printf("Transposição: Qual o nome da matriz?\n");
						a=scanf("%s",nomeMatriz);
						for(i=0;i<numMatriz;i++){
							if(strcmp(vetorMatriz[i].nome,nomeMatriz)==0){	
								matrizA = i;
							}
						}
						if(matrizA==-1){
							printf("Matriz não existente\n\n");
						}
						else{
							vetorMatriz[numMatriz] = matrix_transpose(vetorMatriz[matrizA]);
							printf("Qual o nome da matriz resultante?\n");
							a=scanf("%s",nomeMatriz);
							i=0;
							while(i<numMatriz){
								if(strcmp(vetorMatriz[i].nome,nomeMatriz)==0){
									printf("Nome de matriz já existe, escolha outro nome\n");
									a=scanf("%s",nomeMatriz);
									i=-1;
								}
								i++;
							}
							i=0;
							matrix_rename(&vetorMatriz[numMatriz],nomeMatriz);
							printf("Matriz original a ser transposta\n");
							print_matrix(vetorMatriz[matrizA].nome,vetorMatriz[matrizA]);
							printf("Resultado da transposição:\n");
							print_matrix(vetorMatriz[numMatriz].nome,vetorMatriz[numMatriz]);
							numMatriz++;
						}
						matrizA=-1;
						break;
					case 2:
						printf("Determinante: Qual o nome da matriz?\n");
						a=scanf("%s",nomeMatriz);
						for(i=0;i<numMatriz;i++){
							if(strcmp(vetorMatriz[i].nome,nomeMatriz)==0){	
								matrizA = i;
							}
						}
						if(matrizA==-1){
							printf("Matriz não existente\n\n");
						}
						else{
							if(vetorMatriz[matrizA].nlins!=vetorMatriz[matrizA].ncols){
                						printf("Número de linhas deve ser igual ao número de colunas!\n");
            						}
							else{
								determinante = det(vetorMatriz[matrizA]);
								printf("Matriz escolhida:\n");
								print_matrix(vetorMatriz[matrizA].nome,vetorMatriz[matrizA]);
								printf("Determinante da matriz %s é: %lf\n", vetorMatriz[matrizA].nome,determinante);
							}
						}
						matrizA=-1;
						break;
					case 3:
						printf("Inversão: Qual o nome da matriz?\n");
						a=scanf("%s",nomeMatriz);
						for(i=0;i<numMatriz;i++){
							if(strcmp(vetorMatriz[i].nome,nomeMatriz)==0){	
								matrizA = i;
							}
						}
						if(matrizA==-1){
							printf("Matriz não existente\n\n");
						}
						else{
							if(det(vetorMatriz[matrizA])==0){
                						printf("Determinante da matriz é zero, não existe inversa!\n");
          						}
           						else if(vetorMatriz[matrizA].nlins!=vetorMatriz[matrizA].ncols){
                						printf("Número de linhas deve ser igual ao número de colunas!\n");
            						}
							else{
							vetorMatriz[numMatriz] = matrix_inverse2(vetorMatriz[matrizA]);
							printf("Qual o nome da matriz resultante?\n");
							a=scanf("%s",nomeMatriz);
							i=0;
							while(i<numMatriz){
								if(strcmp(vetorMatriz[i].nome,nomeMatriz)==0){
									printf("Nome de matriz já existe, escolha outro nome\n");
									a=scanf("%s",nomeMatriz);
									i=-1;
								}
								i++;
							}
							i=0;
							matrix_rename(&vetorMatriz[numMatriz],nomeMatriz);
							printf("Matriz original a ser invertida\n");
							print_matrix(vetorMatriz[matrizA].nome,vetorMatriz[matrizA]);
							printf("Resultado da inversão:\n");
							print_matrix(vetorMatriz[numMatriz].nome,vetorMatriz[numMatriz]);
							numMatriz++;
							}
						}
						matrizA=-1;
						break;
					default:
						printf("Operação inválida\n");
				}
				break;
			case 5:
				for(i=0;i<numMatriz;i++){
					print_matrix(vetorMatriz[i].nome,vetorMatriz[i]);
				}
				break;
			case 6:
				printf("Digite o limite inferior, superior e o número de iterações que a integral numérica vai fazer\n");
				a=scanf("%lf",&integral.a);
				a=scanf("%lf",&integral.b);
				a=scanf("%d",&integral.n);
				integralResult = integrar(integral);
				printf("Resultado da integração númerica é: %lf\n\n",integralResult);
				printf("Resultado esperado é: %lf\n\n",funcIntegrada(integral.b)-funcIntegrada(integral.a));
				break;
			case 7:
				for(i=0;i<numMatriz;i++){
					matrix_free(&vetorMatriz[i]);
				}
				printf("Programa encerrado!\n");
				break;
			default:
				 printf("Operação inválida\n");
		}
	}
	return 0;
}
