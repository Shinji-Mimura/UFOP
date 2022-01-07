#ifndef FITAS_H
#define FITAS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "heap.h"

#define FITAS 10

typedef struct fita
{
    FILE *arquivo;
    int qtdBlocos;
    int *numReg;
} Fita;

/* Protótipo de Funções das Fitas*/
void inicializaFitas(Fita *, Fita *);
int getFitasDisponiveis(Fita *);
int isContinua(int *, int);
bool isTudoMarcado(Heap *, int, int);
void desmarcaTudo(Heap *, int, int);

#endif