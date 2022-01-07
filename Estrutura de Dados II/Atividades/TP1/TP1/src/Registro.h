#ifndef REGISTRO_H
#define REGISTRO_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Estrutura do Registro */
typedef struct registro
{
    int chave;
    long int dadoUm;
    char dadoDois[501];
    char dadoTres[3001];
} Registro;

/* Protótipo de funções do Registro */
void imprimeRegistro(Registro *reg);
Registro *iniciaRegistro();

#endif