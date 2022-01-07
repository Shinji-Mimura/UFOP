/*
Aluno: Lucas de Araújo
Matricula: 18.2.4049
Tutor: Marcos Geraldo
Professor: Guilherme
*/

#include <stdio.h>
#include <stdlib.h>

#define MM 2

typedef long TipoChave;
typedef struct TipoPagina *TipoApontador;

typedef struct TipoRegistro
{
    TipoChave Chave;
} TipoRegistro;

typedef struct TipoPagina
{
    short n;
    TipoRegistro r[MM];
    TipoApontador p[MM + 1];
} TipoPagina;

/* Função de Pesquisa (Retorna 1 ou 0) */
short Pesquisa(TipoRegistro *x, TipoApontador Ap)
{
    long i = 1;
    if (Ap == NULL)
    {
        printf("TipoRegistro não está presente na árvore!\n");
        return 0; // Valor não encontrado (inexistente)
    }

    /* Pesquisa Sequencial para se encontrar o intervalo desejado */
    while (i < Ap->n && x->Chave > Ap->r[i - 1].Chave)
    {
        i++;
    }

    if (x->Chave == Ap->r[i - 1].Chave)
    {
        *x = Ap->r[i - 1];
        return 1; //Valor (Chave) foi localizada
    }

    /* Ativação recursiva da pesquisa para alguma das subárvores (esquerda ou direita */
    if (x->Chave < Ap->r[i - 1].Chave)
    {
        Pesquisa(x, Ap->p[i - 1]);
    }

    else
    {
        Pesquisa(x, Ap->p[i]);
    }
}

/* Função para encontrar o maior valor presente em uma árvore B
    A variavél maior é inicializada com 0 quando a função é chamada na main
 */
void Maximo(TipoRegistro *x, TipoApontador Ap, long maior)
{
    int i = 0;

    if (Ap == NULL)
    {
        return; //Árvore vazia
    }

    while (i <= Ap->n)
    {
        Maximo(x, Ap->p[i], maior);
        if (i != Ap->n)
        {
            if (Ap->r[i].Chave > maior)

            {
                maior = Ap->r[i].Chave;
                x->Chave = maior; // Atribui maior valor no registro x
            }

            i++;
        }
    }
}
