#ifndef LERQRY_H
#define LERQRY_H

#include "lista.h"

/**
 * Processa o arquivo comandos.qry.
 * e operações com polígonos (armazenados internamente como filas).
 * * @param bed Caminho do diretório de entrada.
 * @param nomeArq Nome do arquivo .qry.
 * @param pathSaida Caminho do diretório de saída para o SVG/TXT.
 * @param bancoDeDados Lista dinâmica de formas.
 * @param listaPoligonos Lista dinâmica contendo os TADs de Polígonos.
 */

void lerArquivoQry(char *bed, char *nomeArq, char *pathSaida, Lista bancoDeDados, Lista listaPoligonos);

#endif