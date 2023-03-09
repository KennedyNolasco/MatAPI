//Integral
#ifndef INTEGRAL_H
#define INTEGRAL_H

#include <stdio.h>

typedef struct Integral{ 
	int n;
	double a,b; 
	double (*func)(double);
} Integral;

double integrar(Integral integral);

#endif   
