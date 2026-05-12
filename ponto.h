#ifndef PONTO_H
#define PONTO_H

typedef void* Ponto;

Ponto criaPonto(double x, double y);
double getPontoX(Ponto p);
double getPontoY(Ponto p);
void liberaPonto(Ponto p);

#endif