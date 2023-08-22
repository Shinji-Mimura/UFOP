#include "MergeSort.h"

void mergesort(int *v, int esq, int dir)
{
    if (esq < dir)
    {                                // 1
        int meio = (esq + dir) / 2;  // 1
        mergesort(v, esq, meio);     // n/2
        mergesort(v, meio + 1, dir); // n/2
        merge(v, esq, meio, dir);    // 18n - 4 => O(n)
    }
}

void merge(int *v, int esq, int meio, int dir)
{
    int tamV1 = meio - esq + 1; // 1
    int tamV2 = dir - meio;     // 1

    int i; // 1
    int j; // 1
    int k; // 1

    int *V1 = malloc(tamV1 * sizeof(int)); // 1
    int *V2 = malloc(tamV2 * sizeof(int)); // 1
    
    // 3n - 2
    for (i = 0; i < tamV1; i++)  // 2 - n/2
        V1[i] = v[esq + i];      // 1 - (n/2 - 1)
    for (i = 0; i < tamV2; i++)  // 2 - n/2
        V2[i] = v[meio + 1 + i]; // 1 - (n/2 - 1)

    for (i = 0, j = 0, k = esq; k <= dir; k++) // (15n - 11)
    {
        if (i == tamV1)
        {
            v[k] = V2[j];
            j++;
        }
        else if (j == tamV2)
        {
            v[k] = V1[i];
            i++;
        }
        else if (V1[i] < V2[j])
        {
            v[k] = V1[i];
            i++;
        }
        else
        {
            v[k] = V2[j];
            j++;
        }
    }

    // 3n - 2 + 15n - 11 + 9
    // 18n - 4

    free(V1);
    free(V2);
}

/*
- A função 'merge' tem uma complexidade de tempo O(n), uma vez que cada elemento
- dos dois sub-arrays é considerado exatamente uma vez. Desconsiderando os coeficientes
- constantes e os termos menores, a expressão original 18n - 4 se simplifica para O(n).

- A função 'mergesort' implementa uma estratégia de divisão e conquista, dividindo
- o array ao meio até cada sub-array conter apenas um elemento, e depois combinando
- esses sub-arrays de volta. A divisão do array resulta em duas chamadas recursivas
- para 'mergesort', cada uma operando em metade do tamanho do array original, daí
- o termo 2T(n/2) em sua função de complexidade. A função 'mergesort' também chama
- a função 'merge' para combinar os sub-arrays, o que adiciona um tempo de O(n) à
- complexidade total.

- Aplicando o Teorema Mestre para resolver essa recorrência, a complexidade de
- tempo do 'mergesort' é O(n log n).
*/
