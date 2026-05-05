#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "svg.h"
#include "forma.h"

FILE* iniciaSVG(char *path) {
    FILE *svg = fopen(path, "w");
    if (svg == NULL) return NULL;

    fprintf(svg, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    fprintf(svg, "<svg xmlns=\"http://www.w3.org/2000/svg\">\n");
    fflush(svg);
    return svg;
}

void desenhaFiguraSVG(FILE *svg, Figura f) {
    if (svg == NULL || f == NULL) return;

    char tipo = getFormaTipo(f);
    double x = getFormaX1(f);
    double y = getFormaY1(f);
    char *corb = getCorBorda(f);
    char *corp = getCorPreenchimento(f);

    if (tipo == 'r') { 
        double w = getFormaW(f);
        double h = getFormaH(f);
        fprintf(svg, "  <rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" stroke=\"%s\" fill=\"%s\" />\n",
                x, y, w, h, corb, corp);
    } 
    else if (tipo == 'c') { 
    double r = getFormaR(f);
    char *c_borda = getCorBorda(f);
    char *c_preench = getCorPreenchimento(f);

    char *final_borda = (c_borda != NULL && strlen(c_borda) > 0) ? c_borda : "black";
    char *final_fill = (c_preench != NULL && strlen(c_preench) > 0) ? c_preench : "none";

    fprintf(svg, "  <circle cx=\"%f\" cy=\"%f\" r=\"%f\" stroke=\"%s\" fill=\"%s\" />\n",
            x, y, r, final_borda, final_fill);
}
    else if (tipo == 'l') { 
        double x2 = getFormaX2(f);
        double y2 = getFormaY2(f);
        fprintf(svg, "  <line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"%s\" />\n",
                x, y, x2, y2, corb);
    }
    else if (tipo == 't') {
    char* texto = getFormaTexto(f);
    char ancora = getFormaAncora(f);
    char *anchor_svg;

    if (ancora == 'm') anchor_svg = "middle";
    else if (ancora == 'f') anchor_svg = "end";
    else anchor_svg = "start";

    fprintf(svg, "  <text x=\"%f\" y=\"%f\" fill=\"%s\" stroke=\"%s\" text-anchor=\"%s\">%s</text>\n",
            x, y, corp, corb, anchor_svg, texto);
}

    if (isFiguraSelecionada(f)) {
        double ax, ay;
        getAncoraFigura(f, &ax, &ay);
        fprintf(svg, "  <circle cx=\"%f\" cy=\"%f\" r=\"4\" fill=\"none\" stroke=\"red\" stroke-width=\"1\" />\n", ax, ay);
    }
}

void desenhaRetanguloSel(FILE *svg, double x, double y, double w, double h) {
    if (svg == NULL) return;
    fprintf(svg, "  <rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" fill=\"none\" stroke=\"red\" stroke-width=\"2\" stroke-dasharray=\"5,5\" />\n",
            x, y, w, h);
}


void desenhaXExclusao(FILE *svg, double x, double y) {
    if (svg == NULL) return;

    fprintf(svg, "  <line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"red\" stroke-width=\"1\" />\n", x-3, y-3, x+3, y+3);
    fprintf(svg, "  <line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"red\" stroke-width=\"1\" />\n", x-3, y+3, x+3, y-3);
}

void fechaSVG(FILE *svg) {
    if (svg == NULL) return;
    fprintf(svg, "</svg>\n");
    fclose(svg);
}

void removeFigurasComSVG(Lista bancoDeDados, FILE *svg) {
    Iterador it = primeiro(bancoDeDados);
    while (it != NULL) {
        Figura f = getItem(it);
        Iterador prox = proximo(it);

        if (isFiguraSelecionada(f)) {
            double ax, ay;
            getAncoraFigura(f, &ax, &ay);
            
            desenhaXExclusao(svg, ax, ay);
            
            removeLista(bancoDeDados, f);
            liberaFigura(f); 
        }
        it = prox;
    }
}

void finalizaSVG(FILE *svg) {
    if (svg == NULL) {
        return;
    }

    fprintf(svg, "</svg>\n");

    fflush(svg);

    fclose(svg);
    
    printf("Arquivo SVG finalizado com sucesso.\n");
}