#include "Mycomplex.h"

Mycomplex Cmul(Mycomplex a, Mycomplex b)
{
    Mycomplex c;
    c.re=a.re*b.re-a.lm*b.lm;
    c.lm=a.lm*b.re+a.re*b.lm;
    return c;
}