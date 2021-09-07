#include "heap.h"

// Ordena vetor de registros (heap) levando em consideração a marcação
void heapSort(Heap *vetor, int n, Estatisticas *est)
{
    int i = n / 2;
    int pai, filho;
    Heap temp;

    while (true)
    {
        if (i > 0)
        {
            i--;
            temp = vetor[i];
        }

        else
        {
            n--;

            if (n <= 0)
            {
                return;
            }

            temp = vetor[n];
            vetor[n] = vetor[0];
        }

        pai = i;
        filho = i * 2 + 1;

        while (filho < n)
        {
            incComparacao(est);
            if ((filho + 1 < n) && (vetor[filho + 1].marcado > vetor[filho].marcado))
            {
                filho++;
            }

            incComparacao(est);
            if (vetor[filho].marcado > temp.marcado)
            {
                vetor[pai] = vetor[filho];
                pai = filho;
                filho = pai * 2 + 1;
            }

            else
            {
                break;
            }
        }
        vetor[pai] = temp;
    }
}