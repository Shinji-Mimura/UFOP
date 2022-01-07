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

void promoverElemento(FilaPrio* fp, int filho)
{
    int pai;
    struct pacient temp;
    pai = (filho - 1)/2;
    while ((filho > 0) && (fp->dados[pai].prio <= fp->dados[filho].prio))
    {
        temp = fp->dados[filho];
        fp->dados[filho] = fp->dados[pai];
        fp->dados[pai] = temp;

        filho = pai;
        pai = (pai - 1)/2;
    }
    
}

int insere(FilaPrio* fp, char* nome, int prio)
{
    if (fp = NULL || fp->qtd == MAX)
    {
        return 0;
    }

    strcpy(fp->dados[fp->qtd].nome,nome);
    fp->dados[fp->qtd].prio = prio;
    promoverElemento(fp,fp->qtd);
    fp->qtd++;
    return 1;
    
}

void rebaixarElemento(FilaPrio* fp,int pai)
{
    struct pacient temp;
    int filho = 2 * pai + 1;
    while (filho < fp->qtd)
    {
        if (filho < fp->qtd-1)
        {
            if (fp->dados[filho].prio < fp->dados[filho+1].prio)
            {
                filho++;
            }    
        }

        if (fp->dados[pai].prio >= fp->dados[filho].prio)
        {
            break;
        }
        
        temp = fp->dados[pai];
        fp->dados[pai] = fp->dados[filho];
        fp->dados[filho] = temp;

        pai = filho;
        filho = 2 * pai + 1;
    }
    
}

int remove(FilaPrio* fp)
{
    if (fp = NULL || fp->qtd == 0)
    {
        return 0;
    }

    fp->qtd--;
    fp->dados[0] = fp->dados[fp->qtd];
    rebaixarElemento(fp,0);
    return 1;

}

int consulta(FilaPrio* fp, char* nome)
{
    if (fp = NULL || fp->qtd == 0)
    {
        return 0;
    }

    strcpy(nome,fp->dados[0].nome);
    return 1;

}
