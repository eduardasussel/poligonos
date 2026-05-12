#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "poligono.h"
#include "fila.h"
#include "comandos.h"
#include "forma.h"
#include "lista.h"
#include "fila.h"
#include "ponto.h"

typedef struct {
    int id;
    Fila pontos;
} EstruturaPoligono;

Poligono criaPoligono(int id) {
    EstruturaPoligono *p = (EstruturaPoligono*) malloc(sizeof(EstruturaPoligono));
    if (p == NULL) return NULL;

    p->id = id;
    p->pontos = criaFila(); 
    
    return (Poligono)p;
}

void realizaComandoPol(int p_id, int inicial_id, double d, char* corb, char* corp, Lista poligonos, Lista geoLista) {
    Poligono p = buscaPoligono(poligonos, p_id);
    if (p == NULL) return;

    Fila filaPtos = getPontosPoligono(p);
    int n = tamanhoFila(filaPtos);

    if (n < 3) {
        printf("Aviso: Polígono com pontos insuficientes.\n");
        return;
    }

    Lista bordasTemporarias = criaLista();

    Ponto pPrimeiro = (Ponto) desenfileira(filaPtos);
    enfileira(filaPtos, pPrimeiro);
    Ponto anterior = pPrimeiro;

    for (int i = 1; i < n; i++) {
        Ponto atual = (Ponto) desenfileira(filaPtos);
        
        void* linha = criaLinhaStruct(inicial_id++, getPontoX(anterior), getPontoY(anterior), getPontoX(atual), getPontoY(atual), corb);
        
        insereLista(bordasTemporarias, linha); 
        insereLista(geoLista, linha);    
        
        enfileira(filaPtos, atual);
        anterior = atual;
    }

    void* linhaFim = criaLinhaStruct(inicial_id++, getPontoX(anterior), getPontoY(anterior), getPontoX(pPrimeiro), getPontoY(pPrimeiro), corb);
    insereLista(bordasTemporarias, linhaFim);
    insereLista(geoLista, linhaFim);

    preenchePoligono(bordasTemporarias, geoLista, d, corp, &inicial_id);

    destroiListaApenasNos(bordasTemporarias); 
    free(bordasTemporarias);
}

void criaBordasPoligono(Fila filaPtos, Lista geoLista, char* corb, int* id_sequencial) {
    int n = tamanhoFila(filaPtos);
    if (n < 2) return;

    Ponto pPrimeiro = (Ponto) desenfileira(filaPtos);
    enfileira(filaPtos, pPrimeiro);
    
    Ponto pAnterior = pPrimeiro;

    for (int i = 1; i < n; i++) {
        Ponto pCorrente = (Ponto) desenfileira(filaPtos);
        
        void* linha = criaLinhaStruct(*id_sequencial, getPontoX(pAnterior), getPontoY(pAnterior), getPontoX(pCorrente), getPontoY(pCorrente), corb);
        
        if (linha) {
            insereLista(geoLista, linha);
            (*id_sequencial)++;
        }
        
        enfileira(filaPtos, pCorrente);
        pAnterior = pCorrente;
    }

    void* linhaF = criaLinhaStruct(*id_sequencial, getPontoX(pAnterior), getPontoY(pAnterior), getPontoX(pPrimeiro), getPontoY(pPrimeiro), corb);
    
    if (linhaF) {
        insereLista(geoLista, linhaF);
        (*id_sequencial)++;
    }
}

void preenchePoligono(Lista poligLst, Lista preenhLst, double d, char* corp, int* id_sequencial) {
    double xmin, ymin, xmax, ymax;
    determinaBoundingBox(poligLst, &xmin, &ymin, &xmax, &ymax);

   if (d <= 0) return;
    double ycorrente = ymin + (d/2.0);

    while (ycorrente < ymax) {
        Lista coordXLst = criaLista();
        double sweepX1 = xmin - 1.0;
        double sweepX2 = xmax + 1.0;

    for (Iterador it = primeiro(poligLst); it != NULL; it = proximo(it)) {
    void* linhaBorda = getItem(it);
    
    double y1 = getFormaY1(linhaBorda);
    double y2 = getFormaY2(linhaBorda);

    if (y1 == y2) continue;

    double yMaxLinha = (y1 > y2) ? y1 : y2;
    double yMinLinha = (y1 < y2) ? y1 : y2;

    if (ycorrente >= yMinLinha && ycorrente < yMaxLinha) {
        double interceptX;
        if (segmentosInterceptam(sweepX1, sweepX2, ycorrente, linhaBorda, &interceptX)) {
                double *interceptX_ptr = (double*) malloc(sizeof(double));
                if (interceptX_ptr != NULL) {
                    *interceptX_ptr = interceptX;
                    insereListaOrdenado(coordXLst, interceptX_ptr);
                }
            }
        }
        printf("DEBUG: Linha detectada entre Y1: %lf e Y2: %lf\n", y1, y2);
    }
            
        geraLinhasPreenchimento(ycorrente, coordXLst, preenhLst, corp, id_sequencial);
    
        for (Iterador it = primeiro(coordXLst); it != NULL; it = proximo(it)) {
            double *ptr = (double*) getItem(it);
            free(ptr);
        }
        liberaLista(coordXLst);

        ycorrente += d;
        
    }
}

void geraLinhasPreenchimento(double y, Lista coordXLst, Lista preenhLst, char* corp, int* id_sequencial) {
    Iterador it = primeiro(coordXLst);
    
    while (it != NULL) {
        double *x1_ptr = (double*) getItem(it);
        it = proximo(it);
        
        if (it == NULL) break; 
        
        double *x2_ptr = (double*) getItem(it);
        
        if (x1_ptr && x2_ptr) {
            double diff = *x2_ptr - *x1_ptr;
            if (diff > 0.00001) { 
                void* linhaPreench = criaLinhaStruct(*id_sequencial, *x1_ptr, y, *x2_ptr, y, corp);
                if (linhaPreench) {
                    insereLista(preenhLst, linhaPreench);
                    (*id_sequencial)++;
                }
            }
        }
        
        it = proximo(it);
    }
}

void removePontoMaisAntigo(Poligono p) {
    if (p == NULL) return;
    EstruturaPoligono *pol = (EstruturaPoligono*) p;

    Ponto antigo = (Ponto) desenfileira(pol->pontos);
    
    if (antigo != NULL) {
        liberaPonto(antigo); 
    }
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

    if (fabs(ly1 - ly2) < 0.000001) return 0;

    double y_min = (ly1 < ly2) ? ly1 : ly2;
    double y_max = (ly1 > ly2) ? ly1 : ly2;

    if (y >= y_min && y < y_max) {
        double lx1 = getFormaX1(linhaBorda);
        double lx2 = getFormaX2(linhaBorda);
        
        double ix = lx1 + (y - ly1) * (lx2 - lx1) / (ly2 - ly1);
    
        double x_min_sweep = (x1 < x2) ? x1 : x2;
        double x_max_sweep = (x1 > x2) ? x1 : x2;

        if (ix >= x_min_sweep && ix <= x_max_sweep) {
            *interceptX = ix;
            return 1;
        }
    }
    return 0;
}

void determinaBoundingBox(Fila filaPtos, double *xmin, double *ymin, double *xmax, double *ymax) {
    int n = tamanhoFila(filaPtos);
    if (n <= 0) return;

    int inicializado = 0; 

    for (int i = 0; i < n; i++) {
        Ponto p = (Ponto) desenfileira(filaPtos);
        
        if (p != NULL) {
            double x = getPontoX(p);
            double y = getPontoY(p);

            if (!inicializado) {
                *xmin = *xmax = x;
                *ymin = *ymax = y;
                inicializado = 1;
            } else {
                if (x < *xmin) *xmin = x;
                if (x > *xmax) *xmax = x;
                if (y < *ymin) *ymin = y;
                if (y > *ymax) *ymax = y;
            }
        }
        
        enfileira(filaPtos, p); 
    }
}

Fila getPontosPoligono(Poligono p) {
    if (p == NULL) return NULL;
    return ((EstruturaPoligono*)p)->pontos;
}

void enfileiraPontoNoPoligono(Poligono p, Ponto pto) {
    if (p == NULL || pto == NULL) return;
    EstruturaPoligono *pol = (EstruturaPoligono*) p;
    enfileira(pol->pontos, pto);
}

Ponto desenfileiraPontoDoPoligono(Poligono p) {
    if (p == NULL) return NULL;
    EstruturaPoligono *pol = (EstruturaPoligono*) p;
    return (Ponto) desenfileira(pol->pontos);
}