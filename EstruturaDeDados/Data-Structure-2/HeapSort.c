#include<stdio.h>
#include<stdlib.h>

void criaHeap(int *vet, int i, int f)
{
    int aux = vet[i];
    int j = i*2+1;
    while (j <= f)
    {
        if (j < f)
        {
            if (vet[j] < vet[j+1])
            {
                j = j+1;
            }
            
        }
        
        if (aux < vet[j])
        {
            vet[i] = vet[j];
            i = j;
            j = 2*i+1;
        }

        else
        {
            j = f+1;
        }
    }

    vet[i] = aux;
    
}


void HeapSort(int *vet, int N)
{
    int i, aux;
    for ( i = (N-1)/2; i >= 0; i--)
    {
        criaHeap(vet,i,N-1); //cria heap apartir dos dados
    }

    for ( i = N-1; i >= 1; i--)
    {
        aux = vet[0];
        vet[0] = vet[i];
        vet[i] = aux;
        criaHeap(vet,0,i-1); //reconstruir a heap
    }
    
    
}

int main(int argc, char const *argv[])
{
    
    int vetor[5] = {5,4,3,2,1};
    HeapSort(vetor,5);

    for (int i = 0; i < 5; i++)
    {
        printf(" %d ",vetor[i]);
    }
    
    printf("\n");

    return 0;
}
