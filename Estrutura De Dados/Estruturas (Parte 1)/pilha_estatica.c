//Arquivo .c pilha
#include<stdio.h>
#include<stdlib.h>
#include "pilha_estatica.h"

struct aluno{
    int mat;
    char nome[30];
    float n1,n2,n3;
};

struct pilha{
    int qtd;
    struct aluno dados[MAX];
};

//Funções////////////////////////
Pilha* cria()
{
    Pilha *aux;
    aux = malloc(sizeof(struct pilha));
    if (aux != NULL)
    {
        aux->qtd = 0;
    }
    
    return aux;
}

void libera(Pilha *pi)
{
    free(pi);
}

int tamanho(Pilha* pi)
{
    if (pi == NULL)
    {
        return -1;
    }

    else
    {
        return pi->qtd;
    }
}

int cheia(Pilha* pi)
{
    if (pi == NULL)
    {
        return -1;
    }
    return (pi->qtd == MAX);
    
}

int vazia(Pilha* pi)
{
    if (pi == NULL)
    {
        return -1;
    }
    return (pi->qtd == 0);
    
}

int insere(Pilha* pi, struct aluno al)
{
    if (pi == NULL || cheia(pi))
    {
        return 0;
    }
    pi->dados[pi->qtd] = al;
    pi->qtd++;
    return 1; // sucesso na inserção
    
}

int remover(Pilha* pi)
{
    if (pi == NULL || pi->qtd == 0)
    {
        return 0;
    }

    pi->qtd--;
    return 1; //sucesso na remoção

}

int consulta(Pilha* pi, struct aluno *al)
{
    if (pi == NULL || pi->qtd == 0)
    {
        return 0;
    }
    *al = pi->dados[pi->qtd-1];
    return 1; //sucesso na consulta
}

int main(int argc, char const *argv[])
{
    Pilha *pi;
    pi = cria();
    libera(pi);

    return 0;
}
