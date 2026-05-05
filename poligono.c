#include <stdio.h>
#include <stdlib.h>
#include "poligono.h"
#include "fila.h"
#include "comandos.h"
#include "forma.h"
#include "lista.h"
#include "fila.h"

typedef struct {
    double x, y;
} Ponto;

typedef struct {
    int id;
    Fila pontos;
} EstruturaPoligono;

Poligono criaPoligono(int id) {
    EstruturaPoligono *p = (EstruturaPoligono*) malloc(sizeof(EstruturaPoligono));
    p->id = id;
    p->pontos = criaFila();
    return (Poligono)p;
}

void realizaComandoPol(int p_id, int inicial_id, double d, char* corb, char* corp, Lista poligonos, Lista geoLista) {
    Poligono p = buscaPoligono(poligonos, p_id);
    
    if (p == NULL) {
        p = criaPoligono(p_id);
        insereLista(poligonos, p);
    }

    Lista poligLst = criaLista();
    Lista preenhLst = criaLista();
    
    Fila filaPtos = getPontosPoligono(p); 

    criaBordasPoligono(filaPtos, poligLst, corb, &inicial_id);

    preenchePoligono(poligLst, preenhLst, d, corp, &inicial_id);

    transferirItens(poligLst, geoLista);
    transferirItens(preenhLst, geoLista);

    destroiListaApenasNos(poligLst);
    destroiListaApenasNos(preenhLst);
}

void criaBordasPoligono(Fila filaPtos, Lista poligLst, char* corb, int* id_sequencial) {
    if (filaVazia(filaPtos)) {
        printf("DEBUG: Fila de pontos vazia. Ignorando pol.\n");
        return;
    }

    Lista listaPtos = exportarFilaParaLista(filaPtos);
    int qtdPontos = contagemItens(listaPtos);

    if (qtdPontos < 2) { 
        printf("DEBUG: Pontos insuficientes (%d). Ignorando pol.\n", qtdPontos);
        destroiListaApenasNos(listaPtos);
        return;
    }

    Iterador it = primeiro(listaPtos);
    Ponto *primeiroPonto = getItem(it);
    Ponto *ptoAnterior = primeiroPonto;
    
    it = proximo(it);
    while (it != NULL) {
        Ponto *pontoCorrente = getItem(it);
        
        if (ptoAnterior && pontoCorrente) {
            void* linha = criaLinhaStruct(*id_sequencial, ptoAnterior->x, ptoAnterior->y, pontoCorrente->x, pontoCorrente->y, corb);
            if (linha) {
                insereLista(poligLst, linha);
                (*id_sequencial)++;
            }
        }
        ptoAnterior = pontoCorrente;
        it = proximo(it);
    }

    // void* linhaFechamento = criaLinhaStruct(*id_sequencial, ptoAnterior->x, ptoAnterior->y, primeiroPonto->x, primeiroPonto->y, corb);
    // insereLista(poligLst, linhaFechamento);
    // (*id_sequencial)++;

    destroiListaApenasNos(listaPtos);
}

void preenchePoligono(Lista poligLst, Lista preenhLst, double d, char* corp, int* id_sequencial) {
    double xmin, ymin, xmax, ymax;
    determinaBoundingBox(poligLst, &xmin, &ymin, &xmax, &ymax);

    if (d <= 0) return;

    double ycorrente = ymin + (d/2.0);
    while (ycorrente < ymax) {
    ycorrente += d;
}
    
    Lista coordXLst = criaLista();

    while (ycorrente < ymax) {
        double sweepX1 = xmin - 1.0;
        double sweepX2 = xmax + 1.0;

        for (Iterador it = primeiro(poligLst); it != NULL; it = proximo(it)) {
            void* linhaBorda = getItem(it);
            double interceptX;
            
            if (segmentosInterceptam(sweepX1, sweepX2, ycorrente, linhaBorda, &interceptX)) {
                double *interceptX_ptr = (double*) malloc(sizeof(double));
                if (interceptX_ptr != NULL) {
                    *interceptX_ptr = interceptX;
                    insereListaOrdenado(coordXLst, interceptX_ptr);
                }
            }
        }

        geraLinhasPreenchimento(ycorrente, coordXLst, preenhLst, corp, id_sequencial);
        
        limpaListaEItens(coordXLst); 
        
        ycorrente += d;
    }

    liberaLista(coordXLst);
}

void geraLinhasPreenchimento(double y, Lista coordXLst, Lista preenhLst, char* corp, int* id_sequencial) {
    Iterador it = primeiro(coordXLst);
    while (it != NULL) {
        double *xini = getItem(it);
        it = proximo(it);
        if (it == NULL) break;
        double *xfim = getItem(it);
        
        void* linhaPreench = criaLinhaStruct(*id_sequencial, *xini, y, *xfim, y, corp);
        insereLista(preenhLst, linhaPreench);
        
        (*id_sequencial)++;
        it = proximo(it);
    }
}

void inserePontoNoPoligono(Poligono p, double x, double y) {
    EstruturaPoligono *pol = (EstruturaPoligono*) p;
    Ponto *novoPonto = malloc(sizeof(Ponto));
    novoPonto->x = x;
    novoPonto->y = y;
    enfileira(pol->pontos, novoPonto);
}

void removePontoMaisAntigo(Poligono p) {
    EstruturaPoligono *pol = (EstruturaPoligono*) p;
    Ponto *antigo = (Ponto*) desenfileira(pol->pontos);
    if (antigo) free(antigo);
}

Poligono buscaPoligono(Lista listaPoligonos, int id) {
    if (!listaPoligonos) return NULL;

    for (Iterador it = primeiro(listaPoligonos); it != NULL; it = proximo(it)) {
        Poligono p = (Poligono)getItem(it);
        
        if (((EstruturaPoligono*)p)->id == id) {
            return p;
        }
    }
    return NULL;
}

int getIdPoligono(Poligono p) {
    if (p == NULL) return -1; 
    EstruturaPoligono *pol = (EstruturaPoligono*) p;
    return pol->id;
}

int segmentosInterceptam(double x1, double x2, double y, void* linhaBorda, double *interceptX) {
    double ly1 = getFormaY1(linhaBorda);
    double ly2 = getFormaY2(linhaBorda);
    double lx1 = getFormaX1(linhaBorda);
    double lx2 = getFormaX2(linhaBorda);

    double y_min = (ly1 < ly2) ? ly1 : ly2;
    double y_max = (ly1 > ly2) ? ly1 : ly2;

    if (y >= y_min && y < y_max) {
    if (ly2 != ly1) { 
        *interceptX = lx1 + (y - ly1) * (lx2 - lx1) / (ly2 - ly1);
        return 1;
    }
}
    return 0;
}

void determinaBoundingBox(Lista poligLst, double *xmin, double *ymin, double *xmax, double *ymax) {
    Iterador it = primeiro(poligLst);
    if (it == NULL) return;

    void* primeira = getItem(it);
    
    *xmin = getFormaX1(primeira);
    *xmax = getFormaX1(primeira);
    *ymin = getFormaY1(primeira);
    *ymax = getFormaY1(primeira);

    for (it = proximo(it); it != NULL; it = proximo(it)) {
        void* l = getItem(it);
        double lx1 = getFormaX1(l);
        double ly1 = getFormaY1(l);
        double lx2 = getFormaX2(l);
        double ly2 = getFormaY2(l);

        if (lx1 < *xmin) { *xmin = lx1; }
        if (lx2 < *xmin) { *xmin = lx2; }

        if (lx1 > *xmax) { *xmax = lx1; }   
        if (lx2 > *xmax) { *xmax = lx2; }

        if (ly1 < *ymin) { *ymin = ly1; }
        if (ly2 < *ymin) { *ymin = ly2; }

        if (ly1 > *ymax) { *ymax = ly1; }
        if (ly2 > *ymax) { *ymax = ly2; }
    }
}

Fila getPontosPoligono(Poligono p) {
    if (p == NULL) return NULL;
    return ((EstruturaPoligono*)p)->pontos;
}