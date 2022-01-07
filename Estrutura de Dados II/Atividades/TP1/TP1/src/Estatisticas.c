#include "Estatisticas.h"

/*
    A função displayEstatisticas possui alguns códigos de cores da seguinte forma

    - x1b[31m = Vermelho
    - x1b[32m = Verde
    - x1b[33m = Amarelo
    - x1b[34m = Azul
    - x1b[35m = Magenta

    - x1b[0m = Reseta as cores após o uso de determinada cor (serve pra evitar de todo terminal tornar-se uma cor só)

*/

Estatisticas *criaEstatistica() //Inicia estrutura das estatísticas
{
    Estatisticas *nova = (Estatisticas *)malloc(sizeof(Estatisticas));

    nova->num_transferencias = 0;
    nova->num_comparacoes = 0;
    nova->pprocessamento = 0.0;
    nova->pesquisa = 0.0;
    nova->total = 0.0;

    return nova;
}

void displayEstatistica(Estatisticas *est) //Imprime resultados das estatísticas
{
    printf("+-----------------------------+\n");
    printf("|     Estatisticas Finais     |\n");
    printf("+-----------------------------+\n\n");

    printf("Numero de Transferencias Realizadas:\x1b[31m %d \x1b[0m\n", est->num_transferencias);
    printf("Numero de Comparacoes Realizadas:\x1b[32m %d \x1b[0m\n", est->num_comparacoes);
    printf("Tempo Final Gasto (milissegundos) no Pre-Processamento:\x1b[33m %lf \x1b[0m\n", est->pprocessamento);
    printf("Tempo Final Gasto (milissegundos) na Pesquisa:\x1b[34m %lf \x1b[0m\n", est->pesquisa);
    printf("Tempo Final Gasto (milissegundos) na Execucao:\x1b[35m %lf \x1b[0m\n", est->total);

    printf("\n");
}

void incTransferencia(Estatisticas *est) //Incrementa número de transferências
{
    est->num_transferencias++;
}

void incComparacao(Estatisticas *est) //Incrementa número de comparações
{
    est->num_comparacoes++;
}

void iniciaTimePProcessamento(Estatisticas *est) //Inicia variável de tempo no pre-processsamento
{
    est->time_inicioPProcessamento = clock();
}

void encerraTimePProcessamento(Estatisticas *est) //Encerra variável de tempo no pre-processamento
{
    est->time_finalPProcessamento = clock();
    calcPProcessamentoTime(est);
}

void calcPProcessamentoTime(Estatisticas *est) //Calculo do tempo total na fase de pre-processamento
{
    est->pprocessamento = (est->time_finalPProcessamento - est->time_inicioPProcessamento) * 1000.0 / CLOCKS_PER_SEC;
}

void iniciaTimePesquisa(Estatisticas *est) //Inicia variável de tempo na pesquisa
{
    est->time_inicioPesquisa = clock();
}

void encerraTimePesquisa(Estatisticas *est) //Encerra variável de tempo na pesquisa
{
    est->time_finalPesquisa = clock();
    calcTimePesquisa(est);
    calcTimeTotal(est);
}

void calcTimePesquisa(Estatisticas *est) //Calculo do tempo total na fase de pesquisa
{
    est->pesquisa = (est->time_finalPesquisa - est->time_inicioPesquisa) * 1000.0 / CLOCKS_PER_SEC;
}

void calcTimeTotal(Estatisticas *est) //Calculo do tempo total (soma do pre-processamento e pesquisa)
{
    est->total = est->pprocessamento + est->pesquisa;
}