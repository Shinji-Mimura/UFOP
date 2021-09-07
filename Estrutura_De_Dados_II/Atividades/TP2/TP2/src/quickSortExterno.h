#ifndef QUICK_SORT_EXTERNO
#define QUICK_SORT_EXTERNO

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#include "aluno.h"
#include "estatistica.h"

#define TAMAREA 10

#define TRUE 1
#define FALSE 0

void QuickSortExterno(FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, int Esq, int Dir, Estatisticas *est);
void FAVazia(Aluno *Area);
int ObterNumCelOcupadas(Aluno *Area, Estatisticas *est);
void LeSup(FILE **ArqLEs, Aluno *UltLido, int *Ls, short *OndeLer, Estatisticas *est);
void LeInf(FILE **ArqLi, Aluno *UltLido, int *Li, short *OndeLer, Estatisticas *est);
void EscreveMax(FILE **ArqLEs, Aluno R, int *Es, Estatisticas *est);
void EscreveMin(FILE **ArqEi, Aluno R, int *Ei, Estatisticas *est);
void RetiraMax(Aluno *Area, Aluno *R, int *NRArea, Estatisticas *est);
void RetiraMin(Aluno *Area, Aluno *R, int *NRArea, Estatisticas *est);
void RetiraUltimo(Aluno *Area, Aluno *R, Estatisticas *est);
void RetiraPrimeiro(Aluno *Area, Aluno *R, Estatisticas *est);
void InsereItem(Aluno UltLido, Aluno *Area, Estatisticas *est);
void InserirArea(Aluno *Area, Aluno *UltLido, int *NRArea, Estatisticas *est);
void Particao(FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, Aluno *Area, int Esq, int Dir, int *i, int *j, Estatisticas *est);
void imprimirArea(Aluno *Area);

#endif