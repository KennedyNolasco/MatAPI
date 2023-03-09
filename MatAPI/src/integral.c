#include "integral.h"
#include <stdio.h>
#include <math.h>

//Função integradora utilizando Newton-Cotes - regra do trapezio.

double integrar(Integral i1){	

    int i = 1; double area = 0; double h = (i1.b-i1.a)/(i1.n-1);
    double x = i1.a+h;
    while(i <= i1.n-2){

        area = area + i1.func(x)*h;
        x = x+h;
        i++;
    }
    area = area + (i1.func(i1.a) + i1.func(i1.b)) * h/2;

    return area;
}
