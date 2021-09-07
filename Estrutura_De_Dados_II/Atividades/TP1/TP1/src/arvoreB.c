#include "arvoreB.h"

/* Registro = registros, possui chave e dados
 * Página = as páginas do sistema de paginação, com número de posições preenchidas, array de Registro e de ponteiros pras páginas
 * PontPagina = ponteiro para as novas páginas vinculadas.
 */

//Pesquisa retorna 1 ao encontrar o item
int pesquisaBTree(Registro *x, PontPagina pagina, Estatisticas *est)
{
    long i = 1;

    //Verifica se a árvore foi inicializada
    if (pagina == NULL)
    {
        return 0;
    }
    incComparacao(est);

    //busca sequencial pela página desejada
    while ((i < pagina->numero) && (x->chave > pagina->registro[i - 1].chave))
    {
        incComparacao(est);
        i++;
    }

    incComparacao(est);
    //Verifica se o registro foi encontrado
    if (x->chave == pagina->registro[i - 1].chave)
    {
        incComparacao(est);
        *x = pagina->registro[i - 1];
        return 1;
    }

    incComparacao(est);
    //Busca nas próximas subarvores
    if (x->chave < pagina->registro[i - 1].chave)
        return pesquisaBTree(x, pagina->ponteiro[i - 1], est);
    else
        return pesquisaBTree(x, pagina->ponteiro[i], est);
}

//Inicia árvore em memória principal com 'pagina' como o ponteiro para a raiz
void criaArvoreB(FILE *arq, PontPagina *pagina, Estatisticas *est)
{
    Registro registro;
    //Lê a árvore da memória secundária para a memória principal
    incTransferencia(est);
    while (fread(&registro, sizeof(Registro), 1, arq) == 1)
    {
        incTransferencia(est);
        adiciona(registro, pagina, est);
    }
}
//Adiciona registro à árvore B e aumenta a árvore se necessário
void adiciona(Registro reg, PontPagina *pagina, Estatisticas *est)
{
    short cresceu;
    Registro regRetorno;
    Pagina *pagRetorno, *pagTemp;

    //pagRetorno é o filho da direita
    insereArvore(reg, *pagina, &cresceu, &regRetorno, &pagRetorno, est);
    //Verifica se a raiz da arvore cresceu
    if (cresceu)
    {
        //Adiciona outra página raiz
        pagTemp = (Pagina *)malloc(sizeof(Pagina));
        pagTemp->registro[0] = regRetorno;
        pagTemp->numero = 1;
        pagTemp->ponteiro[1] = pagRetorno;
        pagTemp->ponteiro[0] = *pagina;
        *pagina = pagTemp;
    }
}

//Insere valor à árvore e indica se a mesma cresceu
void insereArvore(Registro reg, PontPagina pagina, short *cresceu, Registro *regRetorno, PontPagina *pagRetorno, Estatisticas *est)
{
    long i = 1;
    long j;
    PontPagina pagTemp;

    //Árvore vazia
    if (pagina == NULL)
    {
        *cresceu = 1;
        (*regRetorno) = reg;
        (*pagRetorno) = NULL;
        return;
    }

    incComparacao(est);
    //Pesquisa pela subarvores
    while (i < pagina->numero && reg.chave > pagina->registro[i - 1].chave)
    {
        incComparacao(est);
        i++;
    }
    incComparacao(est);
    if (reg.chave == pagina->registro[i - 1].chave)
    {
        *cresceu = 0;
        return;
    }
    incComparacao(est);
    if (reg.chave < pagina->registro[i - 1].chave)
        i--;
    insereArvore(reg, pagina->ponteiro[i], cresceu, regRetorno, pagRetorno, est);


    if (*cresceu != 1)
        return;


    //Página tem espaço:
    if (pagina->numero < MM)
    {
        insereNaPagina(pagina, *regRetorno, *pagRetorno, est);
        *cresceu = 0;
        return;
    }
    //Página tem que ser dividida: cria-se uma nova página
    pagTemp = (Pagina *)malloc(sizeof(Pagina));
    pagTemp->numero = 0;
    pagTemp->ponteiro[0] = NULL;

    //Nova página com novo registro
    if (i < M + 1)
    {
        //Lending ou empréstimo
        insereNaPagina(pagTemp, pagina->registro[MM - 1], pagina->ponteiro[MM], est);
        pagina->numero--;
        insereNaPagina(pagina, *regRetorno, *pagRetorno, est);
    }
    else
        insereNaPagina(pagTemp, *regRetorno, *pagRetorno, est);

    //balanceamento
    for (j = M + 2; j <= MM; j++)
    {
        insereNaPagina(pagTemp, pagina->registro[j - 1], pagina->ponteiro[j], est);
    }

    pagina->numero = M;
    pagTemp->ponteiro[0] = pagina->ponteiro[M + 1];
    *regRetorno = pagina->registro[M];
    *pagRetorno = pagTemp;
}

//Insere o registro na página
void insereNaPagina(PontPagina pagina, Registro reg, PontPagina pagDir, Estatisticas *est)
{
    short nAchouPosicao = 0;
    int k;
    k = pagina->numero;
    if (k > 0)
        nAchouPosicao = 1;
    //Busca-se a posição da chave na página
    while (nAchouPosicao)
    {
        incComparacao(est);
        //Verifica a posição do registro novo na página
        if (reg.chave >= pagina->registro[k - 1].chave)
        {
            nAchouPosicao = 0;
            break;
        }
        //Empurra os registros pra frente
        pagina->registro[k] = pagina->registro[k - 1];
        pagina->ponteiro[k + 1] = pagina->ponteiro[k];
        k--;
        if (k < 1)
            nAchouPosicao = 0;
    }
    pagina->registro[k] = reg;
    pagina->ponteiro[k + 1] = pagDir;
    pagina->numero++;
}
