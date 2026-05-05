#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lerQry.h"
#include "comandos.h"
#include "poligono.h"
#include "forma.h"
#include "lista.h"
#include "svg.h"

void lerArquivoQry(char *bed, char *nomeArq, char *pathSaida, Lista bancoDeDados, Lista listaPoligonos) {
    char caminhoCompleto[512];
    sprintf(caminhoCompleto, "%s/%s", bed, nomeArq);

    FILE *arq = fopen(caminhoCompleto, "r");
    if (!arq) {
        printf("Erro: Nao foi possivel abrir %s\n", caminhoCompleto);
        return;
    }

    char caminhoSVG[512];
    sprintf(caminhoSVG, "%s/%s.svg", pathSaida, nomeArq);
    FILE *svg = iniciaSVG(caminhoSVG);
    
    char comando[10];
    double x, y, w, h, dx, dy;
    char corb[30], corp[30];
    Poligono poligonoAtual = NULL;

    while (fscanf(arq, "%s", comando) != EOF) {
        printf("Executando comando: %s\n", comando);

        if (strcmp(comando, "inp") == 0) {
    int p_id, i_id;
    fscanf(arq, "%d %d", &p_id, &i_id);
    
    Poligono p = buscaPoligono(listaPoligonos, p_id);
    Figura f = buscaFiguraPorId(bancoDeDados, i_id);

    if (p == NULL) {
        p = criaPoligono(p_id);
        insereLista(listaPoligonos, p);
    }

    if (p != NULL && f != NULL) {
        double x_val, y_val; 

        if (getFormaTipo(f) == 'l') {
            double x1 = getFormaX1(f);
            double y1 = getFormaY1(f);
            double x2 = getFormaX2(f);
            double y2 = getFormaY2(f);

            if (x1 < x2 || (x1 == x2 && y1 < y2)) {
                x_val = x1; y_val = y1;
            } else {
                x_val = x2; y_val = y2;
            }
        } else {
            getAncoraFigura(f, &x_val, &y_val);
        }
        
        inserePontoNoPoligono(p, x_val, y_val);
    }
}
        else if (strcmp(comando, "rmp") == 0) {
            int p_id;
            fscanf(arq, "%d", &p_id); 
            Poligono p = buscaPoligono(listaPoligonos, p_id);
            if (p != NULL) {
                removePontoMaisAntigo(p);
            }
        } 
        else if (strcmp(comando, "pol") == 0) {
            int p_id, i_id;
            double d;
            char corb[30], corp[30];
            fscanf(arq, "%d %d %lf %s %s", &p_id, &i_id, &d, corb, corp);
            realizaComandoPol(p_id, i_id, d, corb, corp, listaPoligonos, bancoDeDados);
        } 
        else if (strcmp(comando, "clp") == 0) {
            int id_clp;
            fscanf(arq, "%d", &id_clp);
            poligonoAtual = buscaPoligono(listaPoligonos, id_clp);
        } 
        else if (strcmp(comando, "sel") == 0) {
            fscanf(arq, "%lf %lf %lf %lf", &x, &y, &w, &h);
            selecionaFigura(x, y, w, h, bancoDeDados);
            desenhaRetanguloSel(svg, x, y, w, h);
        } 
        else if (strcmp(comando, "dels") == 0) {
            removeFigurasComSVG(bancoDeDados, svg);
        } 
        else if (strcmp(comando, "mcs") == 0) {
            fscanf(arq, "%lf %lf %s %s", &dx, &dy, corb, corp);
            modificaFiguras(dx, dy, corb, corp, bancoDeDados);
        }
    }

    Iterador it = primeiro(bancoDeDados);
    while (it != NULL) {
        Figura f = getItem(it);
        desenhaFiguraSVG(svg, f);
        it = proximo(it);
    }

    finalizaSVG(svg); 
    fclose(arq);
}