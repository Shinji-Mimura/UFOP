#ifndef ESTATISTICA_H
#define ESTATISTICA_H
#include <time.h>

typedef struct estatisticas
{
    int num_transferencias_leitura;
    int num_transferencias_escrita;
    int num_comparacoes;

    clock_t time_inicioExecucao;
    clock_t time_finalExecucao;

    double total_execucao;

} Estatisticas;

/* Protótipo das Funções de Estatísticas */
Estatisticas *criaEstatistica();
void displayEstatistica(Estatisticas *est);
void incTransferenciaLeitura(Estatisticas *est);
void incTransferenciaEscrita(Estatisticas *est);
void incComparacao(Estatisticas *est);
void iniciaTimeExecucao(Estatisticas *est);
void encerraTimeExecucao(Estatisticas *est);
void calcTimeExecucao(Estatisticas *est);
#endif