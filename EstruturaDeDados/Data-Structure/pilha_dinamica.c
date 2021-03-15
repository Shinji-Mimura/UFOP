#include<stdlib.h>
#include<stdio.h>
#include "pilha_dinamica.h"

struct aluno
{
    int mat;
    char nome[30];
    float n1,n2,n3;
};

struct elemento
{
    struct aluno dados;
    struct elemento *prox;
};

typedef struct elemento Elem;

//Funções////////////////////

Pilha* cria()
{
    Pilha* aux = malloc(sizeof(Pilha));
    if (aux == NULL)
    {
        *aux = NULL;
    }

    return aux;
    
}

void libera(Pilha *pi)
{
    if (pi != NULL)
    {
        Elem* no;
        while ((*pi) != NULL)
        {
            no = *pi;
            *pi = (*pi)->prox;
            free(no);
        }

        free(pi);
        
    }
    
}

int tamanho(Pilha* pi)
{
    if (pi == NULL)
    {
        return 0;
    }
    int cont = 0;

    Elem* no = *pi;
    while (no != NULL)
    {
        cont++;
        no = no->prox;
    }
    return cont;
    
}

int cheia(Pilha* pi)
{
    return 0;
}

int vazia(Pilha* pi)
{
    if (pi == NULL)
    {
        return 1;
    }

    if (*pi == NULL)
    {
        return 1;
    }
    
    return 0;
}

int insere(Pilha* pi , struct aluno al)
{
    Elem* no = malloc(sizeof(Elem));
    if (pi == NULL || no == NULL)
    {
        return 0;
    }

    no->dados = al;
    no->prox = (*pi);
    *pi = no;
    return 1; //sucesso 
    
}

int remover(Pilha* pi)
{
    if (pi == NULL || (*pi) == NULL)
    {
        return 0;
    }
    Elem* no = *pi;
    *pi = no->prox;
    free(no);
    return 1; //sucesso
    
}

int consulta(Pilha* pi, struct aluno *al)
{
    if (pi == NULL || (*pi) == NULL)
    {
        return 0;
    }

    *al = (*pi)->dados;
    return 1; //sucesso
    
}

////////////////////////////


int main(int argc, char const *argv[])
{
    Pilha *pi;
    pi = cria();
    libera(pi);

    //Struct////
    Aluno aux;
    aux.mat = 1;
    aux.n1 = 8;
    aux.n2 = 9;
    aux.n3 = 10;
    aux.nome;
    ///////////

    insere(pi,aux);
    remover(pi);
    
    return 0;
}
