#ifndef HEAP_H
#define HEAP_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "aluno.h"
#include "estatistica.h"

#define REG 10
struct heap
{
    Aluno registro;
    double marcado; // A marcação em questão é somar um valor grande à nota do aluno
};
typedef struct heap Heap;

void heapSort(Heap *vetor, int n, Estatisticas *est);

#endif