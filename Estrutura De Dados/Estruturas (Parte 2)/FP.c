#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "FP.h"

struct paciente
{
    char nome[30];
    int prio;
};

struct fila_prioridade
{
    int qtd;
    struct paciente dados[MAX];
};

// Para implementação das funções , conferir Lista Estática

int insere(FilaPrio* fp, char* nome, int prio)
{
    if (fp = NULL || fp->qtd == MAX)
    {
        return 0;
    }

    int i = fp->qtd - 1;
    while (i >= 0 && fp->dados[i].prio >= prio)
    {
        fp->dados[i+1] = fp->dados[i];
        i--;
    }

    strcpy(fp->dados[i+1].nome,nome);
    fp->dados[i+1].prio = prio;
    fp->qtd++;
    return 1;
}
    
int remove(FilaPrio* fp)
{
    if (fp = NULL || fp->qtd == 0)
    {
        return 0;
    }

    fp->qtd--;
    return 1;
    
    
}  
    
int consulta(FilaPrio* fp, char* nome)
{
    if (fp = NULL || fp->qtd == 0)
    {
        return 0;
    }

    strcpy(nome,fp->dados[fp->qtd-1].nome);
    return 1;

}

