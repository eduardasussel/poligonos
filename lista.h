#ifndef LISTA_H
#define LISTA_H

typedef void *Lista;
typedef void *Iterador;

Lista criaLista();

void insereLista(Lista l, void *item);

void removeLista(Lista l, void *item);

Iterador primeiro(Lista l);

Iterador proximo(Iterador i);

void *getItem(Iterador i);

void liberaLista(Lista l);

int contagemItens(Lista l);

void destroiListaApenasNos(Lista l);

void* buscaFiguraPorId(Lista l, int id);


#endif