#include <stdlib.h>
#include <stdio.h>

#include "AcSequencial.h"
#include "Arquivo.h"
#include "arvoreB.h"
#include "arvoreBestrela.h"
#include "ArvoreBinaria.h"
#include "Estatisticas.h"
#include "Registro.h"

void verificaInput(int metodo, int situacao, int quantidade)
{
    int erro_detectado = 0;

    if (metodo > 4 || metodo < 1)
    {
        printf("\nMÉTODO INEXISTENTE!\n\n");
        printf("1 - ASI\n2 - Árvore Binaria\n3 - Árvore B\n4 - Árvore B*\n\n");
        erro_detectado = 1;
    }

    if (situacao < 1 || situacao > 3)
    {
        printf("\nSITUAÇÃO INEXISTENTE\n\n");
        printf("1 - Ascendente\n2 - Decrescente\n3 - Aleatória\n\n");
        erro_detectado = 1;
    }

    if (quantidade < 200 || quantidade > 2000000)
    {
        printf("\nQUANTIDADE INVÁLIDA\n\n");
        printf("A quantidade deve estar entre 200 e 2.000.000\n\n");
        erro_detectado = 1;
    }

    if (erro_detectado)
    {
        printf("\nINPUT: ./pesquisa <método> <quantidade> <situação> <chave> [-P]\n\n");

        exit(1);
    }
}

int main(int argc, char *argv[])
{

    int quantidade;
    int metodo;
    int situacao;
    int chave;
    int p;

    metodo = atoi(argv[1]);
    quantidade = atoi(argv[2]);
    situacao = atoi(argv[3]);
    chave = atoi(argv[4]);

    if (argc == 6)
    { //Verificação de argumento opcional -P
        p = !strcmp(argv[5], "-P");
    }
    else
    {
        p = 0;
    }

    verificaInput(metodo, situacao, quantidade);

    if (!iniciaArquivo(quantidade, situacao))
    {
        printf("ERRO NA CRIAÇÃO DO ARQUIVO!\n");
        exit(1);
    }

    FILE *arq;

    if ((arq = fopen("dados.bin", "rb")) == NULL)
    {
        printf("ERRO NA ABERTURA DO ARQUIVO!\n");
        exit(1);
    }

    Estatisticas *ASI, *ArBin, *ArvB, *ArvBStar;
    Registro *regAll = iniciaRegistro();
    regAll->chave = chave;

    /* Variavéis do ASI*/
    int *tabela_asi;

    //Variaveis da Árvore Binária
    Node NoAuxiliar; //Nó Auxiliar da Arvore Binária
    Registro AuxArBin;
    FILE *out;

    //Variaveis da Árvore B
    PontPagina ponteiro = NULL;
    PonteiroS ponteiroS = NULL;

    if (metodo != 1) //É criado um segundo arquivo somente nos métodos de árvore
    {
        if ((out = fopen("out.bin", "w+b")) == NULL)
        {
            printf("ERRO NA ABERTURA DO ARQUIVO DE SAÍDA!\n");
            exit(1);
        }
    }

    switch (metodo)
    {
    case 1: //Acesso Sequencial Indexado
    {

        if (situacao == 3) //Arquivo em ordem aleatória não permite pesquisa de acesso sequencial indexado
        {
            printf("\nARQUIVO NÃO SE ENCONTRA ADEQUADO PARA A EXECUÇÃO DESTE MODO DE PESQUISA\n\n");
            break;
        }

        ASI = criaEstatistica();

        iniciaTimePProcessamento(ASI);
        tabela_asi = constroiIndicePaginas(arq, situacao, ASI);
        encerraTimePProcessamento(ASI);

        iniciaTimePesquisa(ASI);
        if (pesquisaASI(tabela_asi, MAXTABELA, regAll, arq, situacao, ASI))
        {
            encerraTimePesquisa(ASI);
            printf("\nREGISTRO ENCONTRADO!\n\n");
            imprimeRegistro(regAll);
            displayEstatistica(ASI);
        }
        else
        {
            encerraTimePesquisa(ASI);
            printf("\nREGISTRO NÃO ENCONTRADO!\n\n");
            displayEstatistica(ASI);
        }

        free(ASI);

        break;
    }
    case 2: //Arvore Binaria Simulada
    {

        ArBin = criaEstatistica();
        //Pré Processamento do arquivo de entrada para uma Árvore Binária Simulada
        iniciaTimePProcessamento(ArBin);
        criaArvoreBinaria(arq, out, ArBin);
        encerraTimePProcessamento(ArBin);

        AuxArBin.chave = chave;
        //pesquisa na Árvore Binária Simulada
        rewind(out);
        iniciaTimePesquisa(ArBin);

        if (pesquisaArvoreBinaria(out, &NoAuxiliar, AuxArBin, ArBin))
            printf("\nREGISTRO ENCONTRADO! Chave: %d\n\n", chave);
        else
            printf("\nREGISTRO NÃO ENCONTRADO!\n\n");

        encerraTimePesquisa(ArBin);
        displayEstatistica(ArBin);

        free(ArBin);

        break;
    }
    case 3: //Arvore B
    {
        //Criando árvore B a partir da mem. secundária
        ArvB = criaEstatistica();

        iniciaTimePProcessamento(ArvB);
        criaArvoreB(arq, &ponteiro, ArvB);
        encerraTimePProcessamento(ArvB);

        iniciaTimePesquisa(ArvB);
        if (pesquisaBTree(regAll, ponteiro, ArvB))
        {
            encerraTimePesquisa(ArvB);
            printf("\nREGISTRO ENCONTRADO!\n\n");
            imprimeRegistro(regAll);
            displayEstatistica(ArvB);
        }
        else
        {
            encerraTimePesquisa(ArvB);
            printf("\nREGISTRO NÃO ENCONTRADO!\n\n");
            displayEstatistica(ArvB);
        }
        if (p)
            displayArquivo(arq);

        free(ArvB);

        break;
    }
    case 4: //Arvore B*
    {
        //Criando árvore B* a partir da mem. secundária
        ArvBStar = criaEstatistica();

        iniciaTimePProcessamento(ArvBStar);
        criaArvoreBEstrela(arq, &ponteiroS, ArvBStar);
        encerraTimePProcessamento(ArvBStar);

        iniciaTimePesquisa(ArvBStar);
        if (pesquisaBstar(regAll, ponteiroS, ArvBStar))
        {
            encerraTimePesquisa(ArvBStar);
            printf("\nREGISTRO ENCONTRADO!\n\n");
            imprimeRegistro(regAll);
            displayEstatistica(ArvBStar);
        }
        else
        {
            encerraTimePesquisa(ArvBStar);
            printf("\nREGISTRO NÃO ENCONTRADO!\n\n");
            displayEstatistica(ArvBStar);
        }
        if (p)
            displayArquivo(arq);

        free(ArvBStar);

        break;
    }
    default:
    {
        printf("MÉTODO INEXISTENTE\n");
        printf("1 - ASI\n2 - Árvore Binaria\n3 - Árvore B\n4 - Árvore B*\n");
    }
    }

    if (p)
    {
        displayArquivo(arq);
    }

    free(regAll);

    if (metodo != 1) //Fecha arquivo gerado nos métodos de árvores
    {
        fclose(out);
    }

    fclose(arq);
}