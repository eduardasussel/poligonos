#ifndef SVG_H
#define SVG_H

#include <stdio.h>
#include "lista.h"
#include "forma.h"

FILE* iniciaSVG(char *path);

void desenhaBancoNoSVG(FILE *svg, Lista bancoDeDados);

void desenhaFiguraSVG(FILE *svg, Figura f);

void desenhaRetanguloSel(FILE *svg, double x, double y, double w, double h);

void desenhaXExclusao(FILE *svg, double x, double y);

void fechaSVG(FILE *svg);

void removeFigurasComSVG(Lista bancoDeDados, FILE *svg);

void finalizaSVG(FILE *svg);

#endif