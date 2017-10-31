#include "Mycomplex.h"

Mycomplex Cdiv(Mycomplex a, Mycomplex b)
{
    Mycomplex c;
    double r,den;
    if (fabs(b.re) >= fabs(b.lm)) {
        r=b.lm/b.re;
        den=b.re+r*b.lm;
        c.re=(a.re+r*a.lm)/den;
        c.lm=(a.lm-r*a.re)/den;
    } else {
        r=b.re/b.lm;
        den=b.lm+r*b.re;
        c.re=(a.re*r+a.lm)/den;
        c.lm=(a.lm*r-a.re)/den;
    }
    return c;
}
