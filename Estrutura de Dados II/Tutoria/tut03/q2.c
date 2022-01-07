#include <stdio.h>
#include <stdlib.h>

#define MM 4
#define MM2 8

typedef long TipoChave;

typedef struct TipoRegistro
{
    TipoChave chave;
} TipoRegistro;

typedef enum
{
    Interna, // 0
    Externa  // 1
} TipoIntExt;

typedef struct TipoPagina *TipoApontador;

typedef struct TipoPagina
{
    TipoIntExt Pt;
    union
    {
        struct //Página Interna
        {
            int ni;
            TipoChave ri[MM]; // Chaves
            TipoApontador pi[MM + 1];
        } U0;

        struct //Página Externa
        {
            int ne;
            TipoRegistro re[MM2]; // Registros
        } U1;

    } UU;
} TipoPagina;

void Maximo(TipoRegistro *x, TipoApontador *Ap)
{
    int i;
    TipoApontador Pag;
    Pag = *Ap;

    if ((*Ap)->Pt == Interna)
    {
        i = 1;

        while (i < Pag->UU.U0.ni) //Percorre até o último filho da página interna
        {
            i++;
        }

        Pesquisa(x, &Pag->UU.U0.pi[i]);

        return;
    }

    i = 1;

    while (i < Pag->UU.U1.ne) //Percorre até o último elemento da página externa
    {
        i++;
    }

    *x = Pag->UU.U1.re[i - 1]; //Maior Elemento (ultimo elemento da direita)
}