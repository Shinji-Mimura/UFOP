#include "Arquivo.h"
#include "Registro.h"

void arquivoAscendente(int quantidade, Registro *reg, FILE *arq)
{
    reg = iniciaRegistro();

    for (int i = 0; i < quantidade; i++)
    {
        reg->chave = i + 1;

        fwrite(reg, sizeof(Registro), 1, arq);
    }

    free(reg);
}

void arquivoDecrescente(int quantidade, Registro *reg, FILE *arq)
{
    reg = iniciaRegistro();

    for (int i = 0; i < quantidade; i++)
    {
        reg->chave = quantidade - i;

        fwrite(reg, sizeof(Registro), 1, arq);
    }

    free(reg);
}

void arquivoRandom(int quantidade, Registro *reg, FILE *arq, int *array)
{
    reg = iniciaRegistro();

    for (int i = 0; i < quantidade; i++)
    {

        int random_index = rand() % quantidade;
        reg->chave = array[random_index];
        array[random_index] = array[quantidade - 1];
        quantidade--;

        fwrite(reg, sizeof(Registro), 1, arq);
    }

    free(reg);
}

int iniciaArquivo(int quantidade, int ordem)
{
    FILE *arq;
    Registro reg;

    if ((arq = fopen("dados.bin", "wb")) == NULL)
    {
        return 0; // Não foi possível abrir o arquivo
    }

    int *array = malloc(quantidade * sizeof(int));

    for (int i = 0; i < quantidade; i++)
    {
        array[i] = i + 1;
    }

    if (ordem == 1)
    {
        arquivoAscendente(quantidade, &reg, arq);
    }

    else if (ordem == 2)
    {
        arquivoDecrescente(quantidade, &reg, arq);
    }

    else
    {
        arquivoRandom(quantidade, &reg, arq, array);
    }

    free(array);
    fclose(arq);

    return 1; //Arquivo criado com sucesso
}

void displayArquivo(FILE *arq)
{
    Registro reg;
    int i;

    i = 1;

    rewind(arq); //Volta o indicador de posição para o começo do arquivo.

    while (fread(&reg, sizeof(Registro), 1, arq) == 1) //Le até o final do arquivo
    {
        printf("CHAVE [%d]: %d\n", i, reg.chave);
        i++;
    }

    rewind(arq);
}
