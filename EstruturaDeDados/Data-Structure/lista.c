#include<stdio.h>
#include<stdlib.h>
#include"lista.h"

//Estruturas ////////////////////////////////////////////

struct lista{
    ListaNo* prim; // cabeça da lista
};

struct listano
{
    int x;
    ListaNo* prox; // aponta pro próximo elemento
};

///////////////////////////////////////////////////////

// Funções ////////////////////////////////////////////
Lista* cria(){
    Lista* aux = malloc(sizeof(Lista));
    
    aux->prim = NULL;

    return aux;
    
}

void insere_ordenada(Lista* li, int dado){
    ListaNo* ant = NULL;
    ListaNo* p = li->prim;

    while (p != NULL && p->x < dado)
    {
        ant = p;
        p = p->prox;
    }

    ListaNo* novo = (ListaNo*) malloc(sizeof(ListaNo));
    novo->x = dado;

    if (ant == NULL){
        novo->prox = li->prim;
        li->prim = novo;
    }

    else
    {
        novo->prox = ant->prox;
        ant->prox=novo;
    }
    
    
    
}

void insere_inicio(Lista* li, int dado){
    if (li == NULL)
    {
        printf("inválido\n");
    }
    ListaNo* no = malloc(sizeof(ListaNo));
    if (no == NULL)
    {
        printf("Erro na criação do nó\n");
    }

    no->x = dado;
    no->prox = li -> prim;
    li->prim = no;
    
    
}

int vazia(Lista* li){
    return(li->prim == NULL);
}

void imprime(Lista* li){
    for (ListaNo* p = li->prim; p != NULL; p=p->prox)
    {
        printf(" %d ",p->x);
    }
    printf("\n");
    
}

int pertence(Lista* li, int dado){

    int i = 0;

    for (ListaNo* p = li->prim; p != NULL; p=p->prox,i++)
    {
        if (p->x == dado)
        {
            printf("Pertence ! \n");
            printf("Posição : %d\n",i);
            return 0;
        }

    }

    printf("Não Pertence ! \n");

        
    

}

void libera(Lista* li){

    ListaNo* no = li->prim;
    ListaNo* ant = NULL;
    while (no != NULL)
    {
        ant = no;
        no = no->prox;
        free(ant);
        printf("Nó Removido\n");
        
    }

    free(li);

    printf("Lista removida\n");
    

}

void retirar(Lista* li,int dado){

    ListaNo* p = li->prim;
    ListaNo* ant = NULL;
    while (p!=NULL)
    {
        if (p->x == dado)
        {
            
            ant->prox = p->prox;
            free(p);

        }
        
        else
        {
            ant = p;
            p = p->prox;
        }
        
    }
    

}

int tamanho(Lista* li){
    int cont = 0;
    ListaNo* p = li->prim;
    while (p!=NULL)
    {
        cont++;
        p = p->prox;
    }

    return cont;
    
}

int retorna_ultimo(Lista* li){

    ListaNo* p = li->prim;
    ListaNo* ant = NULL;
    while (p != NULL)
    {
        ant = p;
        p = p->prox;
    }


    int valor = ant->x;
    return valor;
    


}

void concatenarListas(Lista* li, Lista* l2){

    ListaNo* p = li->prim; 
    ListaNo* p2 = l2->prim;

    ListaNo* ant = NULL;

    while (p != NULL)
    {
        ant = p;
        p = p->prox;
    }

   

    ant->prox = p2;
   
}

Lista* particiona(Lista* li,int dado){

    ListaNo* p = li->prim; 
    ListaNo* ant = NULL;

    while (p->x != dado)
    {
        ant = p;
        p = p->prox;
    }

    ant->prox = NULL;
   
   Lista* li2 = cria();
   li2->prim = p;
   return li2;




}

/////////////////////////////////////////////////////

//Programa principal

int main(int argc, char const *argv[])
{
    
    Lista *li; //inicio
    li = cria();

    Lista *li2;
    li2 = cria();

    insere_inicio(li,1);
    insere_inicio(li,2);
    insere_inicio(li,3);

    insere_inicio(li2,8);
    insere_inicio(li2,9);
    insere_inicio(li2,11);


    insere_ordenada(li,6);

    insere_inicio(li,5);
    pertence(li,1000);

    imprime(li);
    printf("------------------\n");
    imprime(li2);

    /*int tam = tamanho(li);
    printf("Tamanho da Lista: %d\n",tam);
    int ultimo = retorna_ultimo(li);
    printf("Ultímo da Lista: %d\n",ultimo);*/

    
    concatenarListas(li,li2);
    imprime(li);
    Lista *li3 = cria();
    li3 = particiona(li,6);
    imprime(li3);
    imprime(li);
    libera(li);
    libera(li2);
    libera(li3);
    return 0;
}

