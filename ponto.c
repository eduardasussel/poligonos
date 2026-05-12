#include <stdlib.h>
#include "ponto.h"

typedef struct {
    double x;
    double y;
} EstruturaPonto;

Ponto criaPonto(double x, double y) {
    EstruturaPonto *p = (EstruturaPonto*) malloc(sizeof(EstruturaPonto));
    if (p) {
        p->x = x;
        p->y = y;
    }
    return (Ponto)p;
}

double getPontoX(Ponto p) {
    return ((EstruturaPonto*)p)->x;
}

double getPontoY(Ponto p) {
    return ((EstruturaPonto*)p)->y;
}

void liberaPonto(Ponto p) {
    free(p);
}