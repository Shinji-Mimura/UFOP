#ifndef ESTATISTICAS_H
#define ESTATISTICAS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/* Estrutura responsável por gerenciar dados das estátisticas */
typedef struct estatisticas
{
    int num_transferencias;
    int num_comparacoes;

    clock_t time_inicioPProcessamento;
    clock_t time_finalPProcessamento;
    clock_t time_inicioPesquisa;
    clock_t time_finalPesquisa;

    double pprocessamento;
    double pesquisa;
    double total;

} Estatisticas;

/* Protótipo das Funções */
Estatisticas *criaEstatistica();
void displayEstatistica(Estatisticas *est);
void incTransferencia(Estatisticas *est);
void incComparacao(Estatisticas *est);
void iniciaTimePProcessamento(Estatisticas *est);
void encerraTimePProcessamento(Estatisticas *est);
void calcPProcessamentoTime(Estatisticas *est);
void iniciaTimePesquisa(Estatisticas *est);
void encerraTimePesquisa(Estatisticas *est);
void calcTimePesquisa(Estatisticas *est);
void calcTimeTotal(Estatisticas *est);

#endif