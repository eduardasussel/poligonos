#ifndef POLIGONO_H
#define POLIGONO_H

typedef void *Poligono;
typedef void *ListaFiguras;

void inserePoligono(int p, int i, ListaFiguras lista);

void removeCordenadaAntiga(int p);

void produzConjuntoLinhas(int p, int i, double d, char* corb, char* corp);

void removeCordenadas(int p);

void selecionaFigura(double x, double y, double w, double h, ListaFiguras todas, ListaFiguras selecionadas);

void removeFiguras(double x, double y, double w, double h, ListaFiguras selecionadas);

void modificaFigura(double dx, double dy, char* corb, char* corp, ListaFiguras selecionadas);
#endif