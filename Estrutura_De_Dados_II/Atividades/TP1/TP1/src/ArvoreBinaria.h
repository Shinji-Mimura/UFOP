#ifndef ARVOREBINARIA_H
#define ARVOREBINARIA_H

#include <stdlib.h>
#include <stdio.h>

#include "Registro.h"
#include "Estatisticas.h"

struct arvb
{
    int esq;
    int dir;
    Registro reg;
    int pos;
};

typedef struct arvb Node;

void criaArvoreBinaria(FILE *arqb, FILE *arv, Estatisticas *a);
int pesquisaArvoreBinaria(FILE *arvore, Node *nodeAux, Registro pesquisado, Estatisticas *est);

#endif