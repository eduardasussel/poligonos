#ifndef FORMA_H
#define FORMA_H

typedef void* Figura;

Figura criaLinhaStruct(int id, double x1, double y1, double x2, double y2, char* corp);
Figura criaCirculoStruct(int id, double x, double y, double r, char* corb, char* corp);
Figura criaRetanguloStruct(int id, double x, double y, double w, double h, char* corb, char* corp);
Figura criaTextoStruct(int id, double x, double y, char* corb, char* corp, char ancora, char* texto);

double getFormaX1(Figura fig);
double getFormaY1(Figura fig);
double getFormaX2(Figura fig);
double getFormaY2(Figura fig);
double getFormaW(void* fig);
double getFormaH(void* fig);
double getFormaR(void* fig);
char   getFormaTipo(Figura fig);
int    getFormaId(Figura fig);
char*  getCorBorda(Figura fig);
char*  getCorPreenchimento(Figura fig);
char* getFormaTexto(Figura f);
char getFormaAncora(Figura f);;


void setFormaX1(Figura fig, double x);
void setFormaY1(Figura fig, double y);
void setFormaX2(Figura fig, double x2);
void setFormaY2(Figura fig, double y2);
void setCorBorda(Figura fig, char* cor);
void setCorPreenchimento(Figura fig, char* cor);

void getAncoraFigura(Figura figura, double *x, double *y);
int isFiguraSelecionada(void* fig);
void setFiguraSelecionada(void* fig, int sel);
void liberaFigura(void* fig);

#endif