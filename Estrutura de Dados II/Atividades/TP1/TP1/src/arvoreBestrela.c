#include "arvoreBestrela.h"

//O metodo de pesquisa ira retornar 0 caso nao encontre o item, e 1 caso encontre
int pesquisaBstar(Registro *reg, PonteiroS pag, Estatisticas *est)
{
    long i;

    if (pag == NULL)
    {
        printf("Arvore vazia\n");
        return 0;
    }

    //Pesquisa sequencial na pagina interna
    if (pag->Pt == Interna)
    {
        i = 1;

        incComparacao(est);
        while (i < pag->UU.U0.numeroInt && reg->chave > pag->UU.U0.regInterno[i - 1])
        {
            incComparacao(est);
            i++;
        }

        incComparacao(est);
        //Pesquisa recursiva até encontrar uma página folha
        if (reg->chave < pag->UU.U0.regInterno[i - 1])
            return pesquisaBstar(reg, pag->UU.U0.pontInt[i - 1], est);
        else
            return pesquisaBstar(reg, pag->UU.U0.pontInt[i], est);
    }

    //Pesquisa sequencial na pagina folha
    i = 1;
    incComparacao(est);
    while (i < pag->UU.U1.numeroExt && reg->chave > pag->UU.U1.regExterno[i - 1].chave)
    {
        incComparacao(est);
        i++;
    }

    incComparacao(est);
    if (reg->chave == pag->UU.U1.regExterno[i - 1].chave)
    {
        *reg = pag->UU.U1.regExterno[i - 1];
        return 1;
    }
    else
        return 0;
}

//O metodo criaArvoreBEstrela eh responsavel por criar a arvore B* em memoria principal, tendo Ap como o ponteiro
//para a raiz dessa arvore B*
void criaArvoreBEstrela(FILE *arq, PonteiroS *pag, Estatisticas *est)
{
    Registro r;

    incTransferencia(est);
    while (fread(&r, sizeof(Registro), 1, arq) == 1)
    {
        incTransferencia(est);
        adicionaEstrela(r, pag, est);
    }
}

void adicionaEstrela(Registro Reg, PonteiroS *pag, Estatisticas *est)
{
    short cresceu;
    Registro RegRetorno;
    PaginaS *pagRetorno;
    PaginaS *pagTemp;

    //Insercao do primeiro item em uma arvore B* vazia
    if (*pag == NULL)
    {
        pagTemp = (PaginaS *)malloc(sizeof(PaginaS));
        pagTemp->Pt = Externa;
        pagTemp->UU.U1.numeroExt = 1;
        pagTemp->UU.U1.regExterno[0] = Reg;
        *pag = pagTemp;
        return;
    }
    //Insercao dos demais itens
    else
    {
        insereArvoreEstrela(Reg, *pag, &cresceu, &RegRetorno, &pagRetorno, est);
        //Arvore cresceu na altura pela raiz
        if (cresceu)
        {
            pagTemp = (PaginaS *)malloc(sizeof(PaginaS));
            pagTemp->Pt = Interna;
            pagTemp->UU.U0.numeroInt = 1;
            pagTemp->UU.U0.regInterno[0] = RegRetorno.chave;
            pagTemp->UU.U0.pontInt[1] = pagRetorno;
            pagTemp->UU.U0.pontInt[0] = *pag;
            *pag = pagTemp;
        }
    }
}

void insereArvoreEstrela(Registro Reg, PonteiroS pag, short *cresceu, Registro *RegRetorno, PonteiroS *pagRetorno, Estatisticas *est)
{
    long i = 1;
    long j;
    PonteiroS ApTemp;

    //Caso a pagina seja externa (folha)
    if (pag->Pt == Externa)
    {
        incComparacao(est);
        while (i < pag->UU.U1.numeroExt && Reg.chave > pag->UU.U1.regExterno[i - 1].chave)
        {
            incComparacao(est);
            i++;
        }

        incComparacao(est);
        if (Reg.chave == pag->UU.U1.regExterno[i - 1].chave)
        {
            printf("Registro ja esta presente\n");
            *cresceu = 0;
            return;
        }

        incComparacao(est);
        if (Reg.chave < pag->UU.U1.regExterno[i - 1].chave)
        {
            i--;
        }

        //Página tem espaço
        if (pag->UU.U1.numeroExt < MM)
        {
            *RegRetorno = Reg;
            insereNaPaginaEstrela(pag, *RegRetorno, *pagRetorno, est);
            *cresceu = 0;
            return;
        }
        //Página tem que ser dividida
        ApTemp = (PaginaS *)malloc(sizeof(PaginaS));
        ApTemp->Pt = Externa;
        ApTemp->UU.U1.numeroExt = 0;

        *RegRetorno = Reg;  //retorno recebe o item
        *pagRetorno = NULL; //apontador recebe NULL

        //Nova página com novo registro
        if (i < M + 1)
        {
            insereNaPaginaEstrela(ApTemp, pag->UU.U1.regExterno[MM - 1], *pagRetorno, est);
            pag->UU.U1.numeroExt--;
            insereNaPaginaEstrela(pag, *RegRetorno, *pagRetorno, est);
        }
        //Insercao direta
        else
        {
            insereNaPaginaEstrela(ApTemp, *RegRetorno, *pagRetorno, est);
        }

        //Empurrando
        for (j = 1; j <= M; j++)
        {
            insereNaPaginaEstrela(ApTemp, pag->UU.U1.regExterno[MM - j], *pagRetorno, est);
        }

        pag->UU.U1.numeroExt = M;
        *RegRetorno = pag->UU.U1.regExterno[M];
        *pagRetorno = ApTemp;
        *cresceu = 1;
        return;
    }
    //Caso a pagina seja externa (folha)
    else
    {
        //Mesmo que Árvore B
        incComparacao(est);
        while (i < pag->UU.U0.numeroInt && Reg.chave > pag->UU.U0.regInterno[i - 1])
        {
            incComparacao(est);
            i++;
        }

        incComparacao(est);
        if (Reg.chave == pag->UU.U0.regInterno[i - 1])
        {
            printf("Registro ja esta presente\n");
            *cresceu = 0;
            return;
        }

        incComparacao(est);
        if (Reg.chave < pag->UU.U0.regInterno[i - 1])
            i--;

        insereArvoreEstrela(Reg, pag->UU.U0.pontInt[i], cresceu, RegRetorno, pagRetorno, est);
        if (!*cresceu)
            return;
        //Página tem espaço
        if (pag->UU.U0.numeroInt < MM)
        {
            insereNaPaginaEstrela(pag, *RegRetorno, *pagRetorno, est);
            *cresceu = 0;
            return;
        }
        //Página tem que ser dividida: cria-se uma nova página
        ApTemp = (PaginaS *)malloc(sizeof(PaginaS));
        ApTemp->Pt = Interna;
        ApTemp->UU.U0.numeroInt = 0;
        ApTemp->UU.U0.pontInt[0] = NULL;

        Registro RegAux;

        if (i < M + 1)
        {
            //Lending ou empréstimo
            RegAux.chave = pag->UU.U0.regInterno[MM - 1];
            insereNaPaginaEstrela(ApTemp, RegAux, pag->UU.U0.pontInt[MM], est);
            pag->UU.U0.numeroInt--;
            insereNaPaginaEstrela(pag, *RegRetorno, *pagRetorno, est);
        }
        else
        {
            insereNaPaginaEstrela(ApTemp, *RegRetorno, *pagRetorno, est);
        }

        for (j = M + 2; j <= MM; j++)
        {
            RegAux.chave = pag->UU.U0.regInterno[j - 1];
            insereNaPaginaEstrela(ApTemp, RegAux, pag->UU.U0.pontInt[j], est);
        }

        pag->UU.U0.numeroInt = M;
        ApTemp->UU.U0.pontInt[0] = pag->UU.U0.pontInt[M + 1];
        RegRetorno->chave = pag->UU.U0.regInterno[M];
        *pagRetorno = ApTemp;

        return;
    }
}

void insereNaPaginaEstrela(PonteiroS pag, Registro Reg, PonteiroS pagDir, Estatisticas *est)
{
    short naoAchouPosicao = 0;
    int k;

    //Caso a pagina seja externa (folha)
    //Comportamento igual o da árvore B
    if (pag->Pt == Externa)
    {
        k = pag->UU.U1.numeroExt;
        if (k > 0)
            naoAchouPosicao = 1;
        //Busca a posição da chave na página
        while (naoAchouPosicao)
        {
            incComparacao(est);
            //Verifica a posição do novo registro na página
            if (Reg.chave >= pag->UU.U1.regExterno[k - 1].chave)
            {
                naoAchouPosicao = 0;
                break;
            }
            //Empurra os registros pra frente
            pag->UU.U1.regExterno[k] = pag->UU.U1.regExterno[k - 1];
            k--;
            if (k < 1)
                naoAchouPosicao = 0;
        }
        pag->UU.U1.regExterno[k] = Reg;
        pag->UU.U1.numeroExt++;
    }
    //Caso a pagina seja interna
    else
    {
        k = pag->UU.U0.numeroInt;
        if (k > 0)
            naoAchouPosicao = 1;
        //Busca a posição da chave na página
        while (naoAchouPosicao)
        {
            incComparacao(est);
            //Verifica a posição do novo registro na página
            if (Reg.chave >= pag->UU.U0.regInterno[k - 1])
            {
                naoAchouPosicao = 0;
                break;
            }
            //Empurra os registros pra frente
            pag->UU.U0.regInterno[k] = pag->UU.U0.regInterno[k - 1];
            pag->UU.U0.pontInt[k + 1] = pag->UU.U0.pontInt[k];
            k--;
            if (k < 1)
                naoAchouPosicao = 0;
        }

        pag->UU.U0.regInterno[k] = Reg.chave;
        pag->UU.U0.pontInt[k + 1] = pagDir;
        pag->UU.U0.numeroInt++;
    }
}
