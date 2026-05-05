#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "forma.h"

typedef struct NoLista {
    void *item;
    struct NoLista *prox;
} NoLista;

typedef struct {
    NoLista *cabeca;
    int tamanho;
} EstruturaLista;

Lista criaLista() {
    EstruturaLista *l = (EstruturaLista*) malloc(sizeof(EstruturaLista));
    if (l) {
        l->cabeca = NULL;
        l->tamanho = 0;
    }
    return (Lista)l;
}

void insereLista(Lista l, void *item) {
    if (!l || !item) {
        printf("ERRO: Tentativa de inserir item NULL ou em lista NULL.\n");
        return; 
    }
    
    EstruturaLista *lista = (EstruturaLista*) l;
    printf("DEBUG: Inserindo elemento na lista. Tamanho atual: %d\n", ((EstruturaLista*)l)->tamanho);
    
    NoLista *novo = (NoLista*) malloc(sizeof(NoLista));
    if (!novo) return;

    novo->item = item;
    novo->prox = lista->cabeca;
    lista->cabeca = novo;
    lista->tamanho++;
}

void insereListaOrdenado(Lista l, void *item) {
    if (!l || !item) return;
    EstruturaLista *lista = (EstruturaLista*) l;
    double valorNovo = *(double*)item;

    NoLista *novo = (NoLista*) malloc(sizeof(NoLista));
    novo->item = item;

    NoLista *atual = lista->cabeca;
    NoLista *anterior = NULL;

    while (atual != NULL && *(double*)(atual->item) < valorNovo) {
        anterior = atual;
        atual = atual->prox;
    }

    if (anterior == NULL) { 
        novo->prox = lista->cabeca;
        lista->cabeca = novo;
    } else {
        novo->prox = atual;
        anterior->prox = novo;
    }
    lista->tamanho++;
}

void transferirItens(Lista origem, Lista destino) {
    if (!origem || !destino) return;
    
    for (Iterador it = primeiro(origem); it != NULL; it = proximo(it)) {
        void* item = getItem(it);
        insereLista(destino, item);
    }
}

void limpaListaEItens(Lista l) {
    if (!l) return;
    EstruturaLista *lista = (EstruturaLista*) l;
    NoLista *atual = lista->cabeca;
    
    while (atual != NULL) {
        NoLista *prox = atual->prox;
        if (atual->item) free(atual->item); 
        free(atual);
        atual = prox;
    }
    lista->cabeca = NULL;
    lista->tamanho = 0;
}


Iterador primeiro(Lista l) {
    if (!l) return NULL;
    return (Iterador)((EstruturaLista*)l)->cabeca;
}

Iterador proximo(Iterador i) {
    if (!i) return NULL;
    return (Iterador)((NoLista*)i)->prox;
}

void *getItem(Iterador i) {
    if (!i) return NULL;
    return ((NoLista*)i)->item;
}

void liberaLista(Lista l) {
    if (!l) return;
    limpaListaEItens(l);
    free(l);
}

void removeLista(Lista l, void *item) {
    if (!l || !item) return;
    EstruturaLista *lista = (EstruturaLista*) l;
    NoLista *atual = lista->cabeca;
    NoLista *anterior = NULL;

    while (atual != NULL) {
        if (atual->item == item) {
            if (anterior == NULL) {
                lista->cabeca = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }
            free(atual);
            lista->tamanho--;
            return;
        }
        anterior = atual;
        atual = atual->prox;
    }
}

int contagemItens(Lista l) {
    if (!l) return 0;
    return ((EstruturaLista*)l)->tamanho;
}

void destroiListaApenasNos(Lista l) {
    if (!l) return;
    NoLista *atual = ((EstruturaLista*)l)->cabeca;
    while (atual != NULL) {
        NoLista *prox = atual->prox;
        free(atual);
        atual = prox;
    }
    ((EstruturaLista*)l)->cabeca = NULL;
    ((EstruturaLista*)l)->tamanho = 0;
}

Figura buscaFiguraPorId(Lista l, int id) {
    Iterador it = primeiro(l); 
    while (it != NULL) {
        Figura f = getItem(it);
        if (getFormaId(f) == id) {
            return f;
        }
        it = proximo(it);
    }
    return NULL;
}