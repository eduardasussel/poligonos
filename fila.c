#include <stdlib.h>
#include "fila.h"
#include "lista.h"

#define MAX_FILA 20

typedef struct {
    void* itens[MAX_FILA];
    int frente;
    int final;
    int tamanho;
} EstruturaFila;

Fila criaFila() {
    EstruturaFila *f = (EstruturaFila*) malloc(sizeof(EstruturaFila));
    f->frente = 0;
    f->final = -1;
    f->tamanho = 0;
    return (Fila)f;
}

void enfileira(Fila f, void *item) {
    EstruturaFila *fila = (EstruturaFila*) f;
    if (fila->tamanho == MAX_FILA) return;

    fila->final = (fila->final + 1) % MAX_FILA;
    fila->itens[fila->final] = item;
    fila->tamanho++;
}

void *desenfileira(Fila f) {
    EstruturaFila *fila = (EstruturaFila*) f;
    if (fila->tamanho == 0) return NULL;

    void *item = fila->itens[fila->frente];
    fila->frente = (fila->frente + 1) % MAX_FILA;
    fila->tamanho--;
    return item;
}

int filaVazia(Fila f) {
    EstruturaFila *fila = (EstruturaFila*) f;
    return (fila->frente == NULL);
}
