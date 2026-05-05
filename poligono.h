#ifndef POLIGONO_H
#define POLIGONO_H

#include "fila.h"
#include "lista.h"

typedef void *Poligono;
Poligono criaPoligono(int id);
void realizaComandoPol(int p_id, int inicial_id, double d, char* corb, char* corp, Lista poligonos, Lista geoLista);
void preenchePoligono(Lista poligLst, Lista preenhLst, double d, char* corp, int* id_sequencial);
void geraLinhasPreenchimento(double y, Lista coordXLst, Lista preenhLst, char* corp, int* id_sequencial);
void criaBordasPoligono(Fila filaPtos, Lista poligLst, char* corb, int* id_sequencial);
void inserePontoNoPoligono(Poligono p, double x, double y);
void removePontoMaisAntigo(Poligono p);
void limpaPontosPoligono(Poligono p);
void liberaPoligono(Poligono p);
Poligono buscaPoligono(Lista listaPoligonos, int id);
int getIdPoligono(Poligono p);
int segmentosInterceptam(double x1, double x2, double y, void* linhaBorda, double *interceptX);
void determinaBoundingBox(Lista poligLst, double *xmin, double *ymin, double *xmax, double *ymax);
Fila getPontosPoligono(Poligono p);
void transferirItens(Lista origem, Lista destino);
void insereListaOrdenado(Lista l, void *item);
void limpaListaEItens(Lista l);

#endif