#ifndef TP1ED2_ARVOREB_H
#define TP1ED2_ARVOREB_H

#include "Registro.h"
#include "Estatisticas.h"
#include <stdio.h>
#include <stdlib.h>

#define M 3
#define MM M * 2

//Estruturas
typedef struct Pagina *PontPagina;

typedef struct Pagina
{
    short numero;
    Registro registro[MM];
    PontPagina ponteiro[MM + 1];

} Pagina;

//Protótipos de funções
int pesquisaBTree(Registro *x, PontPagina pagina, Estatisticas *est);

void criaArvoreB(FILE *arq, PontPagina *pagina, Estatisticas *est);

void adiciona(Registro reg, PontPagina *pagina, Estatisticas *est);

void insereArvore(Registro reg, PontPagina pagina, short *cresceu, Registro *regRetorno, PontPagina *pagRetorno, Estatisticas *est);

void insereNaPagina(PontPagina pagina, Registro reg, PontPagina pagDir, Estatisticas *est);

#endif //TP1ED2_ARVOREB_H
