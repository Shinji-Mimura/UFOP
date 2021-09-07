#include "Registro.h"

void imprimeRegistro(Registro *reg) //Imprime dados do registro
{
    printf("+----------------------+\n");
    printf("|   Dados do Registro  |\n");
    printf("+----------------------+\n\n");

    printf("CHAVE: %d\n", reg->chave);
    printf("DADO 1: %ld\n", reg->dadoUm);
    printf("DADO 2: %s\n", reg->dadoDois);
    printf("DADO 3: %s\n", reg->dadoTres);

    printf("\n");
}

Registro *iniciaRegistro()
{
    Registro *novo = (Registro *)malloc(sizeof(Registro));
    novo->chave = -1;
    srand(time(NULL));
    novo->dadoUm = (rand() % 10000000) + 1;
    strcpy(novo->dadoDois, "Show de Bola");
    strcpy(novo->dadoTres, "Show de Bola");

    return novo;
}