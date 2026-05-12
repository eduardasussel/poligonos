#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lerQry.h"
#include "comandos.h"
#include "poligono.h"
#include "forma.h"
#include "lista.h"
#include "svg.h"
#include "fila.h"
#include "ponto.h"

void lerArquivoQry(char *bed, char *nomeArq, char *pathSaida, Lista bancoDeDados, Lista listaPoligonos) {
    char caminhoCompleto[512];
    sprintf(caminhoCompleto, "%s/%s", bed, nomeArq);

    FILE *arq = fopen(caminhoCompleto, "r");
    if (!arq) {
        printf("Erro: Nao foi possivel abrir %s\n", caminhoCompleto);
        return;
    }

    char caminhoSVG[512];
    char caminhoTXT[512];

    sprintf(caminhoSVG, "%s/%s.svg", pathSaida, nomeArq);

    sprintf(caminhoTXT, "%s/%s.txt", pathSaida, nomeArq);

    FILE *svg = iniciaSVG(caminhoSVG);
    FILE *txt = fopen(caminhoTXT, "w");
    
    char comando[10];
    double x, y, w, h, dx, dy;
    char corb[30], corp[30];

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

            if (f != NULL) {
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

                Ponto *pto = criaPonto(x_val, y_val);
                enfileiraPontoNoPoligono(p, pto);
        
                printf("Ponto (%f,%f) inserido no polígono %d\n", x_val, y_val, p_id);

                fprintf(txt, "inp %d %d\n", p_id, i_id);
                fprintf(txt, "Coordenada inserida: (%.2f, %.2f) proveniente da figura ID %d\n\n", x_val, y_val, i_id);
            }

        } else if (strcmp(comando, "rmp") == 0) {
            int p_id;
            fscanf(arq, "%d", &p_id); 
            Poligono p = buscaPoligono(listaPoligonos, p_id);
            Ponto *removido = desenfileiraPontoDoPoligono(p);
            
            fprintf(txt, "rmp %d\n", p_id);
            if (removido) {
                fprintf(txt, "Coordenada removida: (%.2f, %.2f)\n\n", getPontoX(removido), getPontoY(removido));
                liberaPonto(removido);

            }
         } else if (strcmp(comando, "pol") == 0) {
            int p_id, i_id;
            double d;
            char corb[30], corp[30];
            fscanf(arq, "%d %d %lf %s %s", &p_id, &i_id, &d, corb, corp);
            realizaComandoPol(p_id, i_id, d, corb, corp, listaPoligonos, bancoDeDados);

        } else if (strcmp(comando, "clp") == 0) {
    int id_clp;
    fscanf(arq, "%d", &id_clp);
    Poligono p = buscaPoligono(listaPoligonos, id_clp);

    if (p != NULL) {
        while (tamanhoFila(getPontosPoligono(p)) > 0) {
            Ponto pto = desenfileiraPontoDoPoligono(p); 
            
            if (pto != NULL) {
                liberaPonto(pto); 
            }
        }
        printf("Polígono %d esvaziado.\n", id_clp);
    }

        } else if (strcmp(comando, "sel") == 0) {
            fscanf(arq, "%lf %lf %lf %lf", &x, &y, &w, &h);
            fprintf(txt, "sel %.2f %.2f %.2f %.2f\n", x, y, w, h);
            
            selecionaFiguraETxt(x, y, w, h, bancoDeDados, txt); 
            desenhaRetanguloSel(svg, x, y, w, h);

        } else if (strcmp(comando, "dels") == 0) {
            fprintf(txt, "dels\n");

            removeFigurasComSVG(bancoDeDados, svg, txt); 

        }else if (strcmp(comando, "mcs") == 0) {
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
    fclose(txt);
    fclose(arq);
}