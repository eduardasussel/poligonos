#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "forma.h"

struct forma {
    char tipo;
    int id;
    double x, y, r, w, h;
    double x2, y2;        
    char texto[100];      
    char corb[30];
    char corp[30];
    char ancora;
    int selecionada;
};


double getFormaX1(void* fig) {
    return ((struct forma*)fig)->x;
}

double getFormaY1(void* fig) {
    return ((struct forma*)fig)->y;
}

double getFormaX2(void* fig) {
    return ((struct forma*)fig)->x2;
}

double getFormaY2(void* fig) {
    return ((struct forma*)fig)->y2;
}

double getFormaW(void* fig) {
    return ((struct forma*)fig)->w;
}

double getFormaH(void* fig) {
    return ((struct forma*)fig)->h;
}

double getFormaR(void* fig) {
    return ((struct forma*)fig)->r;
}

char getFormaTipo(void* fig) {
    return ((struct forma*)fig)->tipo;
}

int getFormaId(void* fig) {
    return ((struct forma*)fig)->id;
}

char* getCorPreenchimento(void* fig) {
    return ((struct forma*)fig)->corp;
}

char* getCorBorda(void* fig) {
    return ((struct forma*)fig)->corb;
}

char* getFormaTexto(Figura f) {
    struct forma *fig = (struct forma*) f;
    return fig->texto;
}

char getFormaAncora(Figura f) {
    struct forma *fig = (struct forma*) f; 
    return fig->ancora;
}


void setFormaX1(void* fig, double x) {
    ((struct forma*)fig)->x = x;
}

void setFormaY1(void* fig, double y) {
    ((struct forma*)fig)->y = y;
}

void setFormaX2(void* fig, double x2) {
    ((struct forma*)fig)->x2 = x2;
}

void setFormaY2(void* fig, double y2) {
    ((struct forma*)fig)->y2 = y2;
}

void setCorBorda(void* fig, char* cor) {
    if (cor != NULL) {
        memset(((struct forma*)fig)->corb, 0, 30);
        strncpy(((struct forma*)fig)->corb, cor, 29);
        ((struct forma*)fig)->corb[29] = '\0'; 
    }
}

void setCorPreenchimento(void* fig, char* cor) {
    if (cor != NULL) {
        memset(((struct forma*)fig)->corp, 0, 30);
        strncpy(((struct forma*)fig)->corp, cor, 29);
        ((struct forma*)fig)->corp[29] = '\0';
    }
}

Figura criaCirculoStruct(int id, double x, double y, double r, char* corb, char* corp) {
    struct forma *f = (struct forma*) malloc(sizeof(struct forma));
    f->id = id;
    f->tipo = 'c';
    f->x = x;
    f->y = y;
    f->r = r;
    setCorBorda(f, corb);
    setCorBorda(f, corp);
    return (Figura)f;
}

Figura criaRetanguloStruct(int id, double x, double y, double w, double h, char* corb, char* corp) {
    struct forma *f = (struct forma*) malloc(sizeof(struct forma));
    f->id = id;
    f->tipo = 'r';
    f->x = x;
    f->y = y;
    f->w = w;
    f->h = h;
    setCorBorda(f, corb);
    setCorBorda(f, corp);
    return (Figura)f;
}

Figura criaLinhaStruct(int id, double x1, double y1, double x2, double y2, char* corb) {
    struct forma *f = (struct forma*) malloc(sizeof(struct forma));
    f->id = id;
    f->tipo = 'l';
    f->x = x1;
    f->y = y1;
    f->x2 = x2;
    f->y2 = y2;
    setCorBorda(f, corb);
    return (Figura)f;
}

Figura criaTextoStruct(int id, double x, double y, char* corb, char* corp, char ancora, char* texto) {
    struct forma *f = (struct forma*) malloc(sizeof(struct forma));
    f->id = id;
    f->tipo = 't';
    f->x = x;
    f->y = y;
    f->ancora = ancora;
    setCorBorda(f, corb);
    setCorBorda(f, corp);
    memset(f->texto, 0, sizeof(f->texto));
    strncpy(f->texto, texto, sizeof(f->texto) - 1);
    f->texto[sizeof(f->texto) - 1] = '\0';
    return (Figura)f;
}

void getAncoraFigura(Figura figura, double *x, double *y) {
    struct forma *f = (struct forma*) figura;

    switch (f->tipo) {
        case 'l': 
            if (f->x < f->x2) {
                *x = f->x;
                *y = f->y;
            } else if (f->x2 < f->x) {
                *x = f->x2;
                *y = f->y2;
            } else { 
                if (f->y <= f->y2) {
                    *x = f->x;
                    *y = f->y;
                } else {
                    *x = f->x2;
                    *y = f->y2;
                }
            }
            break;

        case 'c':
        case 'r':
        case 't':
        default:
            *x = f->x;
            *y = f->y;
            break;
    }
}

int isFiguraSelecionada(void* fig) {
    return ((struct forma*)fig)->selecionada;
}

void setFiguraSelecionada(void* fig, int sel) {
    ((struct forma*)fig)->selecionada = sel;
}

void liberaFigura(void* fig) {
    if (fig != NULL) {
        free(fig);
    }
}
