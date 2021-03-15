#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void bubble_sort(int *vetor,int tam){
    int continua,aux,fim = tam;

    do
    {
        continua = 0;
        for (int i = 0; i < fim-1; i++)
        {
            if (vetor[i]>vetor[i+1])
            {
                aux = vetor[i];
                vetor[i] = vetor[i+1];
                vetor[i+1] = aux;
                continua = i;
            }
            
        }
    fim--;
    } while (continua != 0);
    
}

void insertion_sort(int *vetor,int tam){

    int aux;
    int j;
    for (int i = 1; i < tam; i++)
    {
        aux = vetor[i];
        for (j = i; (j>0) && (aux<vetor[j-1]); j--)
        {
            vetor[j] = vetor[j-1];
        }

        vetor[j] = aux;
        
    }
    
}

void selection_sort(int *vetor,int tam){

    int menor,troca;
    for (int i = 0; i < tam-1; i++)
    {
        menor = i;
        for (int j = i+1; j < tam; j++)
        {
            if (vetor[j] < vetor[menor])
            {
                menor = j;
            }
            
        }
        if (i != menor)
        {
            troca = vetor[i];
            vetor[i] = vetor[menor];
            vetor[menor] = troca;
        }
        
    }
    

}

void merge(int *vetor,int inicio,int meio , int fim){
    int *temp, p1,p2,tamanho,k;
    int fim1 = 0;
    int fim2 = 0;
    tamanho = fim - inicio + 1;
    p1 = inicio;
    p2 = meio+1;

    temp = malloc(tamanho*sizeof(int));
    if (temp != NULL)
    {
        for (int i = 0; i < tamanho; i++)
        {
            if (!fim1 && !fim2)
            {
                if (vetor[p1] < vetor[p2])
                {
                    temp[i] = vetor[p1++];
                }

                else
                {
                    temp[i] = vetor[p2++];
                }

                if (p1>meio)
                {
                    fim1 = 1;
                }
                
                if (p2>fim)
                {
                    fim2 = 1;
                }
                
                
            }
            else
            {
                if (!fim1)
                {
                   temp[i] = vetor[p1++];
                }

                else
                {
                    temp[i] = vetor[p2++];
                }
                
                
            }
            
            
        }

        for (int j = 0,k = inicio ; j<tamanho; j++,k++)
        {
            vetor[k] = temp[j];
        }
        
        free(temp);
    }
    
}

void merge_sort(int *vetor,int inicio, int fim){
    int meio;
    if (inicio < fim)
    {
        meio = floor((inicio+fim)/2);
        merge_sort(vetor,inicio,meio); //esquerda
        merge_sort(vetor,meio+1,fim); //direita
        merge(vetor,inicio,meio,fim); //combina as 2 metades ordenadas
    }
    
}

void shell_sort(int *vetor, int tamanho){
  int i = (tamanho - 1) / 2;
  int chave, k, aux;

  while (i != 0)
  {
    do
    {
      chave = 1;
      for (k = 0; k < tamanho - i; ++k)
      {
        if (vetor[k] > vetor[k + i])
        {
          aux = vetor[k];
          vetor[k] = vetor[k + i];
          vetor[k + i] = aux;
          chave = 0;
        }
      }
    } while (chave == 0);
    i = i / 2;
  }
}

void imprime(int *vetor,int tam){
    for (int i = 0; i < 15; i++)
    {
        printf(" %d ",vetor[i]);
    }
    printf("\n");
}

int main(int argc, char const *argv[])
{
    
    int vetor[15] = {42,91,65,67,94,88,14,67,57,4,40,71,12,75,68};
    
    //Bubble
    //bubble_sort(vetor,15);

    printf("BUBBLE SORT :\n");

    imprime(vetor,15);

    printf("----------------------------------------------------------------\n");
    
    //Insertion
    //insertion_sort(vetor,15);

    printf("INSERTION SORT :\n");

    imprime(vetor,15);

    printf("----------------------------------------------------------------\n");

    //Selection
    //selection_sort(vetor,15);

    printf("SELECTION SORT :\n");

    imprime(vetor,15);

    printf("----------------------------------------------------------------\n");

    //Merge
    //merge_sort(vetor,0,14);

    printf("MERGE SORT :\n");

    imprime(vetor,15);

    printf("----------------------------------------------------------------\n");

    //Shell
    
    shell_sort(vetor,15);

    printf("SHELL SORT :\n");

    imprime(vetor,15);

    printf("----------------------------------------------------------------\n");


    return 0;
}
