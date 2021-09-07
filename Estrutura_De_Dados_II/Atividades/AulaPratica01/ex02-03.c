#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int matricula;
    char nome[35];
    double notas[3];
    int faltas;
} Aluno;

char calcConceito(double n1, double n2, double n3, int faltas)
{

    if (faltas > 18)
    {
        return 'F';
    }

    else
    {
        float media = (n1 + n2 + n3) / 3;

        if (media < 6.0)
        {
            return 'E';
        }

        else if (media >= 6.0 && media < 7.5)
        {
            return 'C';
        }

        else if (media >= 7.5 && media < 9.0)
        {
            return 'B';
        }

        else if (media >= 9.0 && media <= 10)
        {
            return 'A';
        }

        else
        {
            return 'X';
        }
    }
}

int main(int argc, char const *argv[])
{

    Aluno alunos;

    FILE *arq;
    FILE *arq2;

    if ((arq = fopen("alunos.txt", "r")) == NULL)
    {
        printf("Arquivo não pode ser aberto!");
        return 0;
    }

    else
    {
        arq2 = fopen("alunos.bin", "wb");
        while (fscanf(arq, "%d %[A-Z a-z] %lf %lf %lf %d \n", &alunos.matricula, alunos.nome, &alunos.notas[0], &alunos.notas[1], &alunos.notas[2], &alunos.faltas) != EOF)
        {
            fwrite(&alunos, sizeof(alunos), 1, arq2);
        }
        fclose(arq);
        fclose(arq2);
        arq = fopen("alunos.bin", "rb");
        arq2 = fopen("conceitos.txt", "w");
        while (fread(&alunos, sizeof(alunos), 1, arq) == 1)
        {
            printf("%d %s %lf %lf %lf %d \n", alunos.matricula, alunos.nome, alunos.notas[0], alunos.notas[1], alunos.notas[2], alunos.faltas);
            char conceito = calcConceito(alunos.notas[0], alunos.notas[1], alunos.notas[2], alunos.faltas);
            fprintf(arq2, "%d %s %c \n", alunos.matricula, alunos.nome, conceito);
        }
    }

    fclose(arq);
    fclose(arq2);

    return 0;
}
