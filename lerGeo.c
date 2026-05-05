#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lerGeo.h"
#include "lista.h"
#include "forma.h"    

void lerArquivoGeo(char *bed, char *nomeArq, Lista bancoDeDados, Lista listaPoligonos) {
    char caminhoCompleto[512];
    sprintf(caminhoCompleto, "%s/%s", bed, nomeArq);

    FILE *arq = fopen(caminhoCompleto, "r");
    if (!arq) {
        printf("Erro: Nao foi possivel abrir %s\n", caminhoCompleto);
        return;
    }

    char comando[10];
    while (fscanf(arq, "%s", comando) != EOF) {
        
        if (strcmp(comando, "c") == 0) {
            int id; double x, y, r; 
            char corb[30], corp[30];
            fscanf(arq, "%d %lf %lf %lf %s %s", &id, &x, &y, &r, corb, corp);
            Figura f = criaCirculoStruct(id, x, y, r, corb, corp);
            insereLista(bancoDeDados, f);
        } 
        
        else if (strcmp(comando, "r") == 0) {
            int id; double x, y, w, h; 
            char corb[30], corp[30];
            fscanf(arq, "%d %lf %lf %lf %lf %s %s", &id, &x, &y, &w, &h, corb, corp);
            Figura f = criaRetanguloStruct(id, x, y, w, h, corb, corp);
            insereLista(bancoDeDados, f);
        }

        else if (strcmp(comando, "l") == 0) {
            int id; double x1, y1, x2, y2; char cor[30];
            if (fscanf(arq, "%d %lf %lf %lf %lf %s", &id, &x1, &y1, &x2, &y2, cor) == 6) {
            Figura f = criaLinhaStruct(id, x1, y1, x2, y2, cor);
            insereLista(bancoDeDados, f);
    }
}

        else if (strcmp(comando, "t") == 0) {
            int id; double x, y;
            char corb[30], corp[30], txt[100], ancora;
            fscanf(arq, "%d %lf %lf %s %s %c %[^\n]", &id, &x, &y, corb, corp, &ancora, txt);

            Figura f = criaTextoStruct(id, x, y, corb, corp, ancora, txt);
            insereLista(bancoDeDados, f);
        }
    }

    printf("Leitura GEO concluida. %d figuras carregadas.\n", contagemItens(bancoDeDados));
    fclose(arq);
}