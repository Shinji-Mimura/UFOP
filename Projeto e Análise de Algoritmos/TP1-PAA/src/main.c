#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "InsertionSort.h"
#include "RadixSort.h"
#include "MergeSort.h"

void checaOp(int op, int tamanho)
{
    if (op > 3 || op < 1 || (tamanho != 10 && tamanho != 100 && tamanho != 1000 && tamanho != 10000 && tamanho != 100000 && tamanho != 1000000))
    {
        printf("\n==================== ERRO! ====================\n");
        printf("A opção fornecida é inválida!\n");
        printf("Por favor, insira uma opção válida e um tamanho adequado para a execução.\n\n");

        printf("Opções Válidas:\n");
        printf("1 - Insertion Sort\n");
        printf("2 - Merge Sort\n");
        printf("3 - Radix Sort\n\n");

        printf("Tamanhos Válidos: 10, 100, 1000, 10000, 100000, 1000000\n\n");

        printf("FORMATO DE EXECUÇÃO CORRETA: ./main <OPÇÃO> <TAMANHO>\n");
        printf("Exemplo: ./tp1 1 1000\n");
        printf("=================================================\n");

        exit(0);
    }
}

int main(int argc, char const *argv[])
{

    int op = atoi(argv[1]); // Opção de algoritmo selecionada

    int tamanho = atoi(argv[2]); // tamanho do instância que será ordenada
    checaOp(op, tamanho);
    int *valores = (int *)malloc(tamanho * sizeof(int)); // variável para armazenar valores do arquivo de entrada

    double tempo[20];                            // variável que armazena cada iteração das instâncias
    FILE *instancia;                             // arquivo de instância
    clock_t inicio, fim;                         // varíaveis auxiliares para cronometrar tempo
    char caminho_arq[100];                       // variável para armazenar caminho até arquivo de entrada
    char *algoritmo = malloc(30 * sizeof(char)); // variável para armazenar nome do algoritmo;

    for (int i = 1; i <= 20; i++)
    {
        sprintf(caminho_arq, "../input/n%d/instance-n%d-%d.in", tamanho, tamanho, i);
        instancia = fopen(caminho_arq, "r");

        for (int j = 0; j < tamanho; j++)
        {
            fscanf(instancia, "%d", &valores[j]);
        }

        if (op == 1)
        {
            strcpy(algoritmo, "Insertion Sort");
            inicio = clock();
            insertionSort(valores, tamanho);
            fim = clock();
        }

        else if (op == 2)
        {
            strcpy(algoritmo, "Merge Sort");
            inicio = clock();
            mergesort (valores, 0, tamanho - 1);
            fim = clock();
        }

        else if (op == 3)
        {
            strcpy(algoritmo, "Radix Sort");
            inicio = clock();
            radixsort(valores, tamanho);
            fim = clock();
        }

        tempo[i] = (double)(fim - inicio) / CLOCKS_PER_SEC;

        fclose(instancia);
    }

    double media = 0.0;

    printf("%s\n\n", algoritmo);

    for (int i = 1; i <= 20; i++)
    {
        printf("Instancia %2d: %.6lf\n", i, tempo[i - 1]);
        media += tempo[i - 1];
    }

    media = media / 20.0;

    printf("\nTempo Médio: %.6lf\n", media);

    free(valores);
    free(algoritmo);

    return 0;
}
