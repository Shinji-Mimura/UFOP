#include<stdio.h>
#include<stdlib.h>
#include "lista_estatica.h"

struct aluno
{
    int mat;
    float n1,n2,n3;
};

struct lista
{
    int qtd;
    struct aluno dados[MAX];
};

//Funções////////
Lista* cria()
{
    Lista *li;
    li = malloc(sizeof(struct lista));
    if (li != NULL)
    {
        li->qtd = 0;
    }

    return li;
    
}

void libera(Lista* li)
{
    free(li);
}

int insere_final(Lista* li, struct aluno al)
{
    if (li == NULL)
    {
        return 0;
    }

    li->dados[li->qtd] = al;
    li->qtd++;
    return 1; //sucesso
    
}


int insere_inicio(Lista* li, struct aluno al)
{
    if (li == NULL)
    {
        return 0;
    }

    int i;
    for (i = li->qtd-1; i >= 0; i--)
    {
        li->dados[i+1] = li->dados[i];
    }
    li->dados[0] = al;
    li->qtd++;
    return 1; //sucesso
    
    
}

int insere_ordenada(Lista* li, struct aluno al)
{
    if (li == NULL)
    {
        return 0;
    }

    int k,i=0;
    while (i<li->qtd && li->dados[i].mat < al.mat)
    {
        i++;
    }

    for ( k = li->qtd-1; k>=i; i--)
    {
        li->dados[k+1] = li->dados[k];
    }

    li->dados[i] = al;
    li->qtd++;
    
    
}

Lista* particiona(Lista* li, int matr)
{
    Lista* li2 = cria();
    int i=0;
    while (i<li->qtd || li->dados[i].mat != matr)
    {
        i++;
    }

    li2->qtd = li->qtd - i;
    int k = 0;

    while (k < li2->qtd)
    {
        li2->dados[k].mat = li->dados[k+i].mat;
        k++;
    }

    return li2;
    

    
}

void concatena(Lista* li,Lista* li2)
{
    int aux = li->qtd;
    li->qtd = li->qtd + li2->qtd-1;
    int i = 0;
    while (i < li2->qtd)
    {
        li->dados[aux+i] = li2->dados[i];
    }
    

}

int main(int argc, char const *argv[])
{
    Lista *li;
    li = cria();
    libera(li);
    return 0;
}
