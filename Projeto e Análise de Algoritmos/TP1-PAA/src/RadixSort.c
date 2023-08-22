#include "RadixSort.h"

int findMax(int *arr, int size)
{
    int max = arr[0];
    for (int i = 1; i < size; i++) // n
        if (arr[i] > max)
            max = arr[i];

    return max;
}

void countingSort(int *arr, int size, int place)
{
    const int max = findMax(arr, size);
    int output[size];
    int count[max];

    for (int i = 0; i < max; ++i) // Custo: k + 1
        count[i] = 0;

    for (int i = 0; i < size; i++) // Custo: n + 1
        count[(arr[i] / place) % max]++;

    for (int i = 1; i < max; i++) // Custo: k
        count[i] += count[i - 1];

    for (int i = size - 1; i >= 0; i--) // Custo: n + 1
    {
        output[count[(arr[i] / place) % max] - 1] = arr[i];
        count[(arr[i] / place) % max]--;
    }

    for (int i = 0; i < size; i++) // Custo: n + 1
        arr[i] = output[i];
}

void radixsort(int *arr, int size)
{
    int max = findMax(arr, size);

    for (int place = 1; max / place > 0; place *= 10)
        countingSort(arr, size, place);
}

/*
* Análise da Complexidade Temporal do Algoritmo Radix Sort

* FindMax: A complexidade de tempo é linear, ou seja, O(n), onde n é o número de elementos no array.
* CountingSort: A complexidade de tempo é linear, tanto em relação ao número de elementos (n) quanto ao número de dígitos possíveis (k), simplificando O(3n + 2k + 4) para O(n + k).
* RadixSort: A complexidade de tempo inclui a soma da complexidade do FindMax e o produto da complexidade do CountingSort pelo número de dígitos no maior número (P), simplificando O(n) + P * O(n + k) para O(n + k).

- Concluindo, a complexidade de tempo final, considerando P e K constantes, será O(n).

# Análise do Melhor Caso:

* No caso em que o array já está ordenado, a complexidade temporal do Radix Sort é linear, tanto em relação ao número de elementos (n) quanto ao número de dígitos do maior número (k), ou seja, Omega(n + k).

# Análise do Pior Caso:

* Independentemente da ordem dos elementos no array, o Radix Sort percorrerá todos os dígitos de todos os números. Portanto, a complexidade de tempo do pior caso é idêntica à do melhor caso, ou seja, O(n + k).

# Análise do Caso Médio:

* Considerando a natureza independente da ordem dos elementos do algoritmo Radix Sort, a complexidade de tempo média é a mesma que para o melhor e o pior caso. Portanto, a complexidade de tempo média é Theta(n + k).
*/
