#ifndef FILA_H
#define FILA_H

typedef void *Fila;
typedef void *Lista;

Fila criaFila();
void enfileira(Fila f, void *item);
void *desenfileira(Fila f);
int filaVazia(Fila f);
void liberaFila(Fila f);
Lista exportarFilaParaLista(Fila f);

#endif