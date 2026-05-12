#include <stdlib.h>
#include "fila.h"
#include "lista.h"

#define MAX_FILA 1000

typedef struct {
    void* itens[MAX_FILA];
    int frente;
    int final;
    int nItens;
} EstruturaFila;

Fila criaFila() {
    EstruturaFila *f = (EstruturaFila*) malloc(sizeof(EstruturaFila));
    f->frente = 0;
    f->final = -1;
    f->nItens = 0;
    return (Fila)f;
}

void enfileira(Fila f, void *item) {
    EstruturaFila *fila = (EstruturaFila*) f;
    if (fila->nItens == MAX_FILA) return;

    fila->final = (fila->final + 1) % MAX_FILA;
    fila->itens[fila->final] = item;
    fila->nItens++;
}

void* desenfileira(Fila f) {
    EstruturaFila *fila = (EstruturaFila*) f;
    
    if (fila == NULL || fila->nItens == 0) {
        return NULL; 
    }

    void *item = fila->itens[fila->frente];
    fila->frente = (fila->frente + 1) % MAX_FILA;
    fila->nItens--;
    
    return item;
}

int filaVazia(Fila f) {
    EstruturaFila *fila = (EstruturaFila*) f;

    return (fila->nItens == 0); 
}

int tamanhoFila(Fila f) {
    return ((EstruturaFila*)f)->nItens;
}
