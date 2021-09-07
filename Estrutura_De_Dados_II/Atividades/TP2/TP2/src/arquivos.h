#ifndef ARQUIVOS_H
#define ARQUIVOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Protótipo das Funções de Arquivo */
void criarArquivos(FILE **ArqLEs, FILE **ArqLi, FILE **ArqEi, FILE **ArqTexto, int situacao, int quantidade);
void converterBin(FILE *arqOriginal, FILE *arqBin, int quantidade);
void extraiNItens(FILE *arqOriginal, FILE *arqBin, int quantidade);
void imprimeArquivo(FILE *arq, int quant);

#endif