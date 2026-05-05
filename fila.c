#include <stdlib.h>
#include "fila.h"
#include "lista.h"

typedef struct No {
    void *item;
    struct No *prox;
} No;

typedef struct {
    No *frente;
    No *final;
} EstruturaFila;

Fila criaFila() {
    EstruturaFila *f = (EstruturaFila*) malloc(sizeof(EstruturaFila));
    f->frente = f->final = NULL;
    return (Fila)f;
}

void enfileira(Fila f, void *item) {
    EstruturaFila *fila = (EstruturaFila*) f;
    No *novo = (No*) malloc(sizeof(No));
    novo->item = item;
    novo->prox = NULL;
    if (fila->final == NULL) {
        fila->frente = fila->final = novo;
        return;
    }
    fila->final->prox = novo;
    fila->final = novo;
}

void *desenfileira(Fila f) {
    EstruturaFila *fila = (EstruturaFila*) f;
    if (fila->frente == NULL) return NULL;
    No *temp = fila->frente;
    void *item = temp->item;
    fila->frente = fila->frente->prox;
    if (fila->frente == NULL) fila->final = NULL;
    free(temp);
    return item;
}

int filaVazia(Fila f) {
    EstruturaFila *fila = (EstruturaFila*) f;
    return (fila->frente == NULL);
}

void liberaFila(Fila f) {
    while (!filaVazia(f)) {
        desenfileira(f);
    }
    free(f);
}

Lista exportarFilaParaLista(Fila f) {
    EstruturaFila *fila = (EstruturaFila*) f;
    Lista l = criaLista();
    No *atual = fila->frente;
    while (atual != NULL) {
        insereLista(l, atual->item);
        atual = atual->prox;
    }
    return l;
}