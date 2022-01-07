#include "arquivos.h"
#include "aluno.h"

//Função que gera os arquivos de todos os métodos
void criarArquivos(FILE **ArqLEs, FILE **ArqLi, FILE **ArqEi, FILE **ArqTexto, int situacao, int quantidade)
{
    FILE *arqBin;

    switch (situacao)
    {
    case 1: //Arquivo Ordenado Ascendentemente
    {
        if ((arqBin = fopen("PROVAO_ORDENADO.bin", "wb")) == NULL)
            exit(1);

        converterBin(*ArqTexto, arqBin, quantidade);

        fclose(arqBin);

        if ((*ArqLi = fopen("PROVAO_ORDENADO.bin", "r+b")) == NULL)
            exit(1);

        if ((*ArqEi = fopen("PROVAO_ORDENADO.bin", "r+b")) == NULL)
            exit(1);

        if ((*ArqLEs = fopen("PROVAO_ORDENADO.bin", "r+b")) == NULL)
            exit(1);

        break;
    }

    case 2: //Arquivo Ordenado Descendentemente
    {
        if ((arqBin = fopen("PROVAO_INVERSO.bin", "wb")) == NULL)
            exit(1);

        converterBin(*ArqTexto, arqBin, quantidade);

        fclose(arqBin);

        if ((*ArqLi = fopen("PROVAO_INVERSO.bin", "r+b")) == NULL)
            exit(1);

        if ((*ArqEi = fopen("PROVAO_INVERSO.bin", "r+b")) == NULL)
            exit(1);

        if ((*ArqLEs = fopen("PROVAO_INVERSO.bin", "r+b")) == NULL)
            exit(1);

        break;
    }

    case 3: //Arquivo Ordenado Aleatoriamente
    {
        if ((arqBin = fopen("PROVAO_RANDOM.bin", "wb")) == NULL)
            exit(1);

        converterBin(*ArqTexto, arqBin, quantidade);

        fclose(arqBin);

        if ((*ArqLi = fopen("PROVAO_RANDOM.bin", "r+b")) == NULL)
            exit(1);

        if ((*ArqEi = fopen("PROVAO_RANDOM.bin", "r+b")) == NULL)
            exit(1);

        if ((*ArqLEs = fopen("PROVAO_RANDOM.bin", "r+b")) == NULL)
            exit(1);

        break;
    }
    }
}

//Converte arquivos texto em binário
void converterBin(FILE *arqOriginal, FILE *arqBin, int quantidade)
{

    if (arqOriginal == NULL || arqBin == NULL)
    {
        printf("ERRO: Arquivos não puderam ser abertos!\n");
        exit(1);
    }

    Aluno aux;

    int i = 0;

    while (i < quantidade)
    {
        fscanf(arqOriginal, "%ld %lf ", &aux.inscricao, &aux.nota);
        fgets(aux.estado, 3, arqOriginal);
        fseek(arqOriginal, SEEK_CUR, SEEK_CUR);
        fgets(aux.cidade, 50, arqOriginal);
        fseek(arqOriginal, SEEK_END, SEEK_CUR);
        fgets(aux.curso, 30, arqOriginal);

        fwrite(&aux, sizeof(Aluno), 1, arqBin);

        i++;
    }
}

//Extrai N itens de um arquivo binário e salva em outro temporário para futuro acesso do método
void extraiNItens(FILE *arqOriginal, FILE *arqBin, int quantidade)
{
    if (arqOriginal == NULL || arqBin == NULL)
    {
        printf("ERRO: Arquivos não puderam ser abertos!\n");
        exit(1);
    }

    int i = 0;
    Aluno aluno;
    while (i < quantidade)
    {
        fread(&aluno, sizeof(Aluno), 1, arqOriginal);
        fwrite(&aluno, sizeof(Aluno), 1, arqBin);

        i++;
    }
    fclose(arqOriginal);
    rewind(arqBin);
}

//Imprime arquivos
void imprimeArquivo(FILE *arq, int quant)
{
    Aluno a;
    int i = 1;

    rewind(arq);
    while (i <= quant && fread(&a, sizeof(Aluno), 1, arq) == 1)
    {
        imprimeAluno(a);
        i++;
    }
    rewind(arq);
}