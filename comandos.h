#ifndef COMANDOS_H
#define COMANDOS_H

#include "lista.h"
#include "fila.h"

void inicializaComandos();

void inserePoligono(int p_id, double x, double y, Lista BancoDeDados);

void removeCordenadaAntiga(int p_id, Lista BancoDeDados);

void selecionaFigura(double x, double y, double w, double h, Lista BancoDeDados);

void removeFiguras(Lista BancoDeDados);

void modificaFiguras(double dx, double dy, char* corb, char* corp, Lista bancoDeDados);

void inicializaComandos();

int estaDentroDaRegiao(void* figura, double x, double y, double w, double h);

void atualizaPosicao(void* figura, double dx, double dy);

void atualizaCores(void* figura, char* corb, char* corp);

void removeCordenadas(int p_id, Lista BancoDeDados);

void produzConjuntoLinhas(int p_id, double d, char* corb, char* corp, Lista BancoDeDados);

#endif