#include "aluno.h"

//Imprime os dados de um aluno
void imprimeAluno(Aluno a)
{
    printf("%ld\t", a.inscricao);
    printf("%.2lf\t", a.nota);
    printf("%-2s\t", a.estado);
    printf("%-30s\t", a.cidade);
    printf("%-50s", a.curso);
    printf("\n");
}
