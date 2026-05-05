#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "lista.h"
#include "lerQry.h"
#include "lerGeo.h"
#include "comandos.h"
#include "forma.h"
#include "svg.h"


int main(int argc, char *argv[]) {
    char *bed = "C:/ED/poligonos/entradas";  
    char *bsd = "C:/ED/poligonos/saidas";
    char *arqGeo = "arq.geo";
    char *arqsQry[100]; 
    int qtdQry = 0;
    int opt;


    while ((opt = getopt(argc, argv, "e:f:o:q:")) != -1) {
        switch (opt) {
            case 'e': bed = optarg; break;
            case 'f': arqGeo = optarg; break;
            case 'o': bsd = optarg; break;
            case 'q':

                if (qtdQry < 100) {
                    arqsQry[qtdQry++] = optarg;
                }
                break;
            default:
                fprintf(stderr, "Uso: %s -f arq.geo -o bsd [-e bed] [-q arq.qry]\n", argv[0]);
                exit(1);
        }
    }

    if (arqGeo == NULL || bsd == NULL) {
        printf("Erro: Argumentos -f (arquivo geo) e -o (diretorio saida) sao obrigatorios!\n");
        return 1;
    }

    char caminhoCompletoGeo[255];
    sprintf(caminhoCompletoGeo, "%s/%s", bed, arqGeo);

    printf("Lendo arquivo: %s\n", caminhoCompletoGeo);
    printf("Resultados serao salvos em: %s\n", bsd);

    Lista bancoDeDados = criaLista();
    Lista listaPoligonos = criaLista();
    inicializaComandos();

    if (arqGeo != NULL) {
        printf("Processando consultas: %s\n", arqGeo);
        lerArquivoGeo(bed, arqGeo, bancoDeDados, listaPoligonos);
    }

    for (int i = 0; i < qtdQry; i++) {
        printf("Processando consultas: %s\n", arqsQry[i]);

        lerArquivoQry(bed, arqsQry[i], bsd, bancoDeDados, listaPoligonos);
    }

    FILE *arquivoSvg = iniciaSVG(bsd);
        if (arquivoSvg != NULL) {
        for (void* node = primeiro(bancoDeDados); node != NULL; node = proximo(node)) {
            Figura f = getItem(node);
            desenhaFiguraSVG(arquivoSvg, f);
    }
    fechaSVG(arquivoSvg);
}
    
    liberaLista(bancoDeDados);

    return 0;
}