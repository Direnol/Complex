#ifndef COMPLEX_LIBRARY_H
#define COMPLEX_LIBRARY_H

#include <math.h>

typedef struct {
    double re, lm;
} Mycomplex ;

Mycomplex add(Mycomplex a, Mycomplex b);
Mycomplex sub(Mycomplex a, Mycomplex b);
Mycomplex mul(Mycomplex a, Mycomplex b);
Mycomplex div(Mycomplex a, Mycomplex b);

#endif