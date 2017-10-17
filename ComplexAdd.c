#include "Mycomplex.h"

Mycomplex add(Mycomplex a, Mycomplex b)
{
    Mycomplex c;
    c.re=a.re+b.re;
    c.lm=a.lm+b.lm;
    return c;
}