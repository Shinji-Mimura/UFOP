#include<stdio.h>
#include<stdlib.h>
#include "fila.h"

struct fila{
    struct elemento *inicio;
    struct elemento *final;
};

struct elemento{
    struct aluno dados;
    struct elemento *prox;
};

typedef struct elemento Elem;

Fila* criaFila(){
    
    Fila* aux = malloc(sizeof(Fila));
    if(aux != NULL){
        aux->final = NULL;
        aux->inicio = NULL;
    }
    
    return aux;
}

void libera_fila(Fila* fi){
    if (fi != NULL)
    {
        Elem* no;
        while (fi->inicio != NULL)
        {
            no = fi->inicio;
            fi->inicio = fi->inicio->prox;
            free(no);
        }
        free(fi);
    }
    

}

void insere(Fila* fi,int x){
    if (fi == NULL){} 
        printf("Não é possível inserir");
    }

    Elem* no = malloc(sizeof(Elem));
    if (no == NULL){
        printf("Não é possível inserir");

    }

    no->dados = al;
    no->prox = NULL;

    if (fi->final == NULL)
    {
        fi->inicio = no;
    }
    else
    {
        fi->final->prox = no;
    }
    fi->final = no;
    s
    
    
    

}

int main(){
    
    Fila* fi;
    fi = criaFila();
    libera_fila(fi);
    int x = 10;
    insere(fi,x);

    
    
}
