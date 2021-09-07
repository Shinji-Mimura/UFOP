#ifndef MAINRAPUNZEL_C_ARVOREBESTRELA_H
#define MAINRAPUNZEL_C_ARVOREBESTRELA_H

#include "Registro.h"
#include "Estatisticas.h"
#include <stdio.h>
#include <stdlib.h>

#define M 3
#define MM M * 2

//Estruturas
typedef struct PaginaS *PonteiroS;

typedef enum
{
    Interna,
    Externa
} TipoIntExt;

typedef struct PaginaS
{
    TipoIntExt Pt;
    union
    {
        struct
        { //Pagina interna
            int numeroInt;
            int regInterno[MM];
            PonteiroS pontInt[MM + 1];
        } U0;
        struct
        { //Pagina externa (folha)
            int numeroExt;
            Registro regExterno[MM * 2];
        } U1;
    } UU;
} PaginaS;

//Protótipos de funções
int pesquisaBstar(Registro *reg, PonteiroS pag, Estatisticas *est);
void criaArvoreBEstrela(FILE *arq, PonteiroS *pag, Estatisticas *est);
void adicionaEstrela(Registro Reg, PonteiroS *pag, Estatisticas *est);
void insereArvoreEstrela(Registro Reg, PonteiroS pag, short *cresceu, Registro *RegRetorno, PonteiroS *pagRetorno, Estatisticas *est);
void insereNaPaginaEstrela(PonteiroS pag, Registro Reg, PonteiroS pagDir, Estatisticas *est);

#endif //MAINRAPUNZEL_C_ARVOREBESTRELA_H
