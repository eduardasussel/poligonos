#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "poligono.h"

ListaFiguras listaTodas;
ListaFiguras listaSelecionadas;

void setup() {
    for(int i=1; i<=10; i++) {
        removeCordenadas(i);
    }
}

void teste_insercao() {
    printf("Teste inserção");
    setup();
    
    inserePoligono(1, 100, NULL);
    
    printf("OK!\n");
}

void teste_remocao() {
    printf("Teste remoção");
    setup();

    removeCordenadaAntiga(1);
    
    printf("OK!\n");
}

void teste_selecionaFigura() {
    printf("Teste seleciona figura");

    selecionaFigura(0, 0, 50, 50, listaTodas, listaSelecionadas);
    
    printf("OK!\n");
}

void teste_removeFiguras() {
    printf("Teste remove figuras");
    
    removeFiguras(0, 0, 0, 0, listaSelecionadas);
    
    printf("OK!\n");
}

void teste_modificaFigura() {
    printf("Teste modifica figura");

    modificaFigura(5, 5, "red", "green", listaSelecionadas);
    
    printf("OK!\n");
}

void teste_produzConjuntoLinhas() {
    printf("Teste produz conjunto");

    produzConjuntoLinhas(1, 500, 2.0, "black", "red");
    
    printf("OK!\n");
}


int main() {
    listaTodas = NULL; 
    listaSelecionadas = NULL;

    setup(); 
    
    teste_insercao();
    teste_remocao();
    teste_selecionaFigura();
    teste_removeFiguras();
    teste_modificaFigura();
    teste_produzConjuntoLinhas();
    
    printf("=== Todos os testes passaram! ===\n");
    return 0;
}