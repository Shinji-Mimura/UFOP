#ifndef ARQUIVO_H
#define ARQUIVO_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Registro.h"

void arquivoAscendente(int quantidade, Registro *reg, FILE *arq);
void arquivoDecrescente(int quantidade, Registro *reg, FILE *arq);
void arquivoRandom(int quantidade, Registro *reg, FILE *arq, int *array);
int iniciaArquivo(int quantidade, int ordem);
void displayArquivo(FILE *arq);

#endif