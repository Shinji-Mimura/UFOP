#include "AcSequencial.h"
#include "Estatisticas.h"

/* Criação do índice de páginas para armazenar os itens e depois realizar pesquisa */
int *constroiIndicePaginas(FILE *arq, int ordenacao, Estatisticas *est)
{
    int *tabela = malloc(MAXTABELA * sizeof(int));
    Registro reg;
    int i = 0;

    incTransferencia(est);

    while (fread(&reg, sizeof(Registro), 1, arq) == 1)
    {
        incTransferencia(est);
        tabela[i] = reg.chave;
        i++;
        fseek(arq, (ITENSPAGINA - 1) * sizeof(Registro), SEEK_CUR);
    }

    rewind(arq);

    if (ordenacao == 1)
    {
        while (i < MAXTABELA)
        {
            tabela[i] = 1000000000;
            i++;
        }
    }
    else
    {
        while (i < MAXTABELA)
        {
            tabela[i] = -1000000000;
            i++;
        }
    }

    return tabela;
}

/* 
* Pesquisa utilizando Acesso Sequencial Indexado
* Retorna 1 caso valor seja encontrado
* Retorna 0 caso valor não seja encontrado
*/
int pesquisaASI(int tab[], int tam, Registro *item, FILE *arq, int ordenacao, Estatisticas *est)
{

    Registro pagina[ITENSPAGINA];
    int i;
    int quanti_itens;
    long desloc;

    i = 0;

    incComparacao(est);

    if (ordenacao != 2) // Ordenação decrescente
    {
        while (i < tam && tab[i] <= item->chave) // Realiza procura por qual pagina armazena o item desejado
        {
            incComparacao(est);
            i++;
        }
    }
    else //Ordenção ascendente e aleatória
    {

        while (i < tam && tab[i] >= item->chave) // Realiza procura por qual pagina armazena o item desejado
        {
            incComparacao(est);
            i++;
        }
    }

    if (i == 0) //Chave desejada é menor que primeira chave, logo o item não esta presente no arquivo
    {
        return 0;
    }

    else
    {
        if (i < tam)
        {
            quanti_itens = ITENSPAGINA;
        }
        else
        {
            fseek(arq, 0, SEEK_END);
            quanti_itens = (ftell(arq) / sizeof(Registro)) % ITENSPAGINA;

            if (quanti_itens == 0)
            {
                quanti_itens = ITENSPAGINA; //Pesquisa na última pagina do arquivo caso a mesma esteja completa
            }
        }

        // Lê a pagína desejada do arquivo
        desloc = (i - 1) * ITENSPAGINA * sizeof(Registro);   //Deslocamento para posição da página desejada
        fseek(arq, desloc, SEEK_SET);                        //Posicionamento do leitor dentro do arquivo
        fread(&pagina, sizeof(Registro), quanti_itens, arq); //Traz página para memória principal

        incTransferencia(est);

        for (int i = 0; i < quanti_itens; i++)
        {

            incComparacao(est);

            if (pagina[i].chave == item->chave)
            {

                *item = pagina[i];
                return 1; //Chave encontrada no arquivo
            }
        }

        return 0;
    }
}
