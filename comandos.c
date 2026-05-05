#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "comandos.h"
#include "lista.h"
#include "forma.h"
#include "fila.h"

static Lista figurasSelecionadas = NULL; 

void inicializaComandos() {
    if (figurasSelecionadas != NULL) {
        liberaLista(figurasSelecionadas);
    }
    figurasSelecionadas = criaLista();
}

void selecionaFigura(double x, double y, double w, double h, Lista BancoDeDados) {
    
    destroiListaApenasNos(figurasSelecionadas); 
    figurasSelecionadas = criaLista();

    for (Iterador it = primeiro(BancoDeDados); it != NULL; it = proximo(it)) {
        void* figura = getItem(it);
        if (estaDentroDaRegiao(figura, x, y, w, h)) {
            insereLista(figurasSelecionadas, figura);
        }
    }
    printf("Seleção concluída. %d figuras selecionadas.\n", contagemItens(figurasSelecionadas));
}

void removeCordenadas(int p_id, Lista BancoDeDados) {
    void* fig = buscaFiguraPorId(BancoDeDados, p_id);
    if (fig != NULL) {
        printf("Limpando dados da figura %d\n", p_id);
    }
}

void produzConjuntoLinhas(int p_id, double d, char* corb, char* corp, Lista BancoDeDados) {
    void* fig = buscaFiguraPorId(BancoDeDados, p_id);
    if (fig != NULL) {
        printf("Gerando linhas para a figura %d com offset %f (Cores: %s, %s)\n", p_id, d, corb, corp);
    }
}

void removeFiguras(Lista BancoDeDados) {
    if (figurasSelecionadas == NULL || BancoDeDados == NULL) return;

    Iterador it = primeiro(figurasSelecionadas);
    while (it != NULL) {
        void* fig = getItem(it);
        removeLista(BancoDeDados, fig);
        it = proximo(it);
    }

    destroiListaApenasNos(figurasSelecionadas);
    figurasSelecionadas = criaLista();
}

void modificaFiguras(double dx, double dy, char* corb, char* corp, Lista bancoDeDados) {
    if (bancoDeDados == NULL) return;

    Iterador it = primeiro(bancoDeDados);
    while (it != NULL) {
        void* fig = getItem(it);

        if (isFiguraSelecionada(fig)) {
            
            double x1 = getFormaX1(fig);
            double y1 = getFormaY1(fig);
            setFormaX1(fig, x1 + dx);
            setFormaY1(fig, y1 + dy);

            if (getFormaTipo(fig) == 'l') {
                double x2 = getFormaX2(fig);
                double y2 = getFormaY2(fig);
                setFormaX2(fig, x2 + dx);
                setFormaY2(fig, y2 + dy);
            }

            setCorBorda(fig, corb);
            setCorPreenchimento(fig, corp);
        }
        it = proximo(it);
    }
    printf("Modificacao (mcs) das figuras selecionadas concluida.\n");
}

int estaDentroDaRegiao(void* figura, double x, double y, double w, double h) {
    double fx = getFormaX1(figura);
    double fy = getFormaY1(figura);
    
    if (fx >= x && fx <= (x + w) && fy >= y && fy <= (y + h)) {
        return 1;
    }
    return 0;
}

void atualizaPosicao(void* figura, double dx, double dy) {
    setFormaX1(figura, getFormaX1(figura) + dx);
    setFormaY1(figura, getFormaY1(figura) + dy);
    
    if (getFormaTipo(figura) == 'l') {
        setFormaX2(figura, getFormaX2(figura) + dx);
        setFormaY2(figura, getFormaY2(figura) + dy);
    }
}

void atualizaCores(void* figura, char* corb, char* corp) {
    setCorBorda(figura, corb); 
    setCorPreenchimento(figura, corp);
}
