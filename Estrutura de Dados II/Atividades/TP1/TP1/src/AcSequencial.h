#ifndef ACSEQUENCIAL_H
#define ACSEQUENCIAL_H

#include "Registro.h"
#include "Estatisticas.h"

/* Definição das Macros */
#define ITENSPAGINA 4
#define MAXTABELA 2000000 // Número necessário para realização da pesquisa em arquivos com até 2 milhões de registros

/* Protótipo das Funções */
int *constroiIndicePaginas(FILE *arq, int ordenacao, Estatisticas *est);
int pesquisaASI(int tab[], int tam, Registro *item, FILE *arq, int ordenacao, Estatisticas *est);

#endif