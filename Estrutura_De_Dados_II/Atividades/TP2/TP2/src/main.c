#include "quickSortExterno.h"
#include "arquivos.h"
#include "intercala.h"
#include "estatistica.h"

void verificaInput(int metodo, int situacao, int quantidade)
{
    int erro_detectado = 0;

    if (metodo > 3 || metodo < 1)
    {
        printf("\nMÉTODO INEXISTENTE!\n\n");
        printf("1 - 2F Fitas\n2 - F + 1 Fitas\n3 - Quicksort Externo\n\n");
        erro_detectado = 1;
    }

    if (situacao < 1 || situacao > 3)
    {
        printf("\nSITUAÇÃO INEXISTENTE\n\n");
        printf("1 - Ascendente\n2 - Decrescente\n3 - Aleatória\n\n");
        erro_detectado = 1;
    }

    if (quantidade < 100 || quantidade > 471705)
    {
        printf("\nQUANTIDADE INVÁLIDA\n\n");
        printf("A quantidade deve estar entre 100 e 471.705\n\n");
        erro_detectado = 1;
    }

    if (erro_detectado)
    {
        printf("\nINPUT: ./ordena <método> <quantidade> <situação> [-P]\n\n");

        exit(1);
    }
}

int main(int argc, char *argv[])
{
    //Arquivo que recebe o PROVAO.TXT
    FILE *txt;

    //Arquivo a ser ordenado
    FILE *arq;

    //Arquivos extras utilizadas do quickSort Externo
    FILE *arqEi;
    FILE *arqLEs;

    FILE *bin;

    //Organizando os parâmetros
    int ordena = atoi(argv[1]);
    int quantidade = atoi(argv[2]);
    int situacao = atoi(argv[3]);

    verificaInput(ordena, situacao, quantidade);

    int opcional = 0;
    if (argc == 5)
    {
        if (!strcmp(argv[4], "-P"))
            opcional = 1;
        else
        {
            printf("\nParâmetro -P incorreto!\n\n");
            exit(1);
        }
    }

    //Abrindo o arquivo para ordenação
    switch (situacao)
    {
    case 1: //Arquivo original ordenado ascendentemente
        bin = fopen("PROVAO_CRESCENTE.bin", "r+b");
        arq = fopen("temp.bin", "w+b");

        extraiNItens(bin, arq, quantidade);
        fclose(arq);

        arq = fopen("temp.bin", "r+b");
        break;
    case 2: //Arquivo original ordenado descendentemente
        bin = fopen("PROVAO_DECRESCENTE.bin", "r+b");
        arq = fopen("temp.bin", "w+b");

        extraiNItens(bin, arq, quantidade);
        fclose(arq);

        arq = fopen("temp.bin", "r+b");
        break;
    case 3: //Arquivo original ordenado aleatoriamente
        txt = fopen("PROVAO.TXT", "r");
        arq = fopen("temp.bin", "w+b");

        converterBin(txt, arq, quantidade);
        fclose(txt);
        fclose(arq);

        arq = fopen("temp.bin", "r+b");
        break;

    default: //Situação do arquivo não existente
        printf("ERRO: O parametro de situacao do executavel deve ser de 1 a 3.\n");
        break;
    }

    //Iniciando as estatísticas
    Estatisticas *est = (Estatisticas *)criaEstatistica();

    switch (ordena)
    {
    case 1: //Intercalação Balanceada + Seleção por Substituição
        if (opcional == 1)
        {
            printf("\n");
            printf("+-------------------------------------+\n");
            printf("| ARQUVO ANTES DO MÉTODO DE ORDENAÇÃO |\n");
            printf("+-------------------------------------+\n");
            printf("\n");
            imprimeArquivo(arq, quantidade);
        }
        iniciaTimeExecucao(est);
        intercala2F(arq, quantidade, est);
        encerraTimeExecucao(est);

        break;
    case 2:
        printf("\nF + 1 Fitas em andamento...\n\n");
        break;
    case 3: //QuickSort Externo
        if (opcional == 1)
        {
            printf("\n");
            printf("+-------------------------------------+\n");
            printf("| ARQUVO ANTES DO MÉTODO DE ORDENAÇÃO |\n");
            printf("+-------------------------------------+\n");
            printf("\n");
            imprimeArquivo(arq, quantidade);
        }

        arqEi = fopen("temp.bin", "r+b");
        arqLEs = fopen("temp.bin", "r+b");

        iniciaTimeExecucao(est);
        QuickSortExterno(&arq, &arqEi, &arqLEs, 1, quantidade, est);
        encerraTimeExecucao(est);

        fclose(arqEi);
        fclose(arqLEs);
        rewind(arq);

        break;
    default:
        printf("ERRO: O parametro de ordenacao do executavel deve ser de 1 a 3.\n");
        break;
    }

    //Fechando os arquivos
    fclose(arq);

    if (opcional == 1)
    {
        printf("\n");
        printf("+-----------------------------------+\n");
        printf("| ARQUVO APÓS O MÉTODO DE ORDENAÇÃO |\n");
        printf("+-----------------------------------+\n");
        printf("\n");
        arq = fopen("temp.bin", "r+b");
        imprimeArquivo(arq, quantidade);
        fclose(arq);
    }

    if (ordena != 2)
    {
        displayEstatistica(est);
    }

    free(est);

    return 0;
}