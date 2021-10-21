#include <pre.h>

ELEMENT_ATTRIBUTE* Input_E_A(double A,
                           float E,
                           float G,
                           double I,
                           double L)
{
    ELEMENT_ATTRIBUTE* ptr;
    ptr = (ELEMENT_ATTRIBUTE*)malloc(sizeof(ELEMENT_ATTRIBUTE));
    p->A = A;
    p->E = E;
    p->G = G;
    p->I = I;
    p->L = L;
    return ptr;
}

