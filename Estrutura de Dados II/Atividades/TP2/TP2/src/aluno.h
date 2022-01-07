#ifndef ALUNO_H
#define ALUNO_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct aluno
{
    long int inscricao;
    double nota;
    char estado[3];
    char cidade[51];
    char curso[31];

} Aluno;

/* Protótipo das Funções de Aluno*/
void imprimeAluno(Aluno a);

#endif