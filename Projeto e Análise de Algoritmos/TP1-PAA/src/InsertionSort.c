#include "InsertionSort.h"

void insertionSort(int *arr, int n)
{
    int i, key, j;

    for (i = 1; i < n; i++)
    {

        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}

/*
* Análise de Complexidade do Algoritmo Insertion Sort

# Análise Geral:

- O laço externo é executado n vezes.
- As linhas 10, 11 e 19 juntas totalizam 3(n-1) operações.

- O laço interno é executado Ti + 1 vezes, onde Ti corresponde às execuções das linhas 15 e 16.
- Portanto, o bloco 13-17 tem complexidade (3 * sigma(Ti+1) para i = 1 até n - 1) + (2 * sigma(Ti) para i = 1 até n - 1).

- A função de complexidade temporal, T(n), é então definida como:
  * T(n) = 5n - 3 + 5 * sigma(Ti) + 3 * sigma(1) para i = 1 até n - 1.
  * Simplificando, temos T(n) = 8n - 6 + 5 * sigma(Ti) para i = 1 até n - 1.

# Análise do Melhor Caso (Ti = 0):

- Neste caso, T(n) = 8n - 6, o que implica em uma complexidade temporal de O(n).

# Análise do Pior Caso (Ti = i - 1):

- Aqui, T(n) = 8n - 6 + 5 * sigma(Ti) para i = 0 até n - 2.
- Simplificando, temos T(n) = 8n - 6 + 5 * (0 + (n - 2)) * (n - 1) / 2.
- O resultado é T(n) = (5n² + n - 2) / 2, o que implica em uma complexidade temporal de O(n²).

# Análise do Caso Médio (Ti = i / 2 + sigma(j) para j = 0 até i - 1):

- Aqui, Ti = (i - 1) / 2.
- Então, T(n) = 8n - 6 + 5 * sigma(i / 2) para i = 0 até n - 2.
- Simplificando, temos T(n) = 8n - 6 + 5/2 * (0 + (n - 2)) * (n - 1) / 2.
- O resultado é T(n) = (5n² + 17n - 15), o que implica em uma complexidade temporal de O(n²).
*/
