#ifndef COMPLEX_LIBRARY_H
#define COMPLEX_LIBRARY_H

#include <math.h>

typedef struct {
    double re, lm;
} Mycomplex ;

Mycomplex Cadd(Mycomplex a, Mycomplex b);
Mycomplex Csub(Mycomplex a, Mycomplex b);
Mycomplex Cmul(Mycomplex a, Mycomplex b);
Mycomplex Cdiv(Mycomplex a, Mycomplex b);

#endif