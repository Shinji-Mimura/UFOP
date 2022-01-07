#include<stdio.h>
#include<stdlib.h>

typedef long TChave;

typedef struct {
    TChave chave;
/* outros componentes */
}TItem;

typedef struct No {
    TItem item;
    struct No *pEsq, *pDir;
}TNo;

typedef TNo * TArvore;

void TArvore_Inicia(TNo **pRaiz) {
 *pRaiz = NULL;
}

TNo *TNo_Cria(TItem x){
 TNo *pAux = (TNo*)malloc(sizeof(TNo));
 pAux->item = x;
 pAux->pEsq = NULL;
 pAux->pDir = NULL;
 return pAux;
}

int TArvore_Pesquisa(TArvore pRaiz, TChave c, TItem *pX) {
 if (pRaiz == NULL)
 return 0;

 if (c < pRaiz->item.chave)
 return TArvore_Pesquisa(pRaiz->pEsq, c, pX);
 if (c > pRaiz->item.chave)
 return TArvore_Pesquisa(pRaiz->pDir, c, pX);
 *pX = pRaiz->item;
 return 1;
}

int TArvore_Insere(TNo** ppR, TItem x){
 if (*ppR == NULL) {
 *ppR = TNo_Cria(x);
 return 1;
 }
 if (x.chave < (*ppR)->item.chave)
 return TArvore_Insere(&((*ppR)->pEsq), x);
 if (x.chave > (*ppR)->item.chave)
 return TArvore_Insere(&((*ppR)->pDir), x);
 return 0; // elemento jah existe
}

void TArvore_Sucessor(TNo *q, TNo **r){
 TNo *pAux;
 if ((*r)->pEsq != NULL) {
 TArvore_Sucessor(q, &(*r)->pEsq);
 return;
 }
 q->item = (*r)->item;
 pAux = *r;
 *r = (*r)->pDir;
 free(pAux);
}


int TArvore_Retira(TNo **p, TItem x)
{
    TNo *pAux;
    if (*p == NULL)
    return 0;
    if (x.chave < (*p)->item.chave)
    
    return TArvore_Retira(&((*p)->pEsq), x);

    if (x.chave > (*p)->item.chave)
    return TArvore_Retira(&((*p)->pDir), x);

    if ((*p)->pEsq == NULL && (*p)->pDir == NULL) { // no eh folha
    free(*p);
    *p = NULL;
    return 1;
    }
    if ((*p)->pEsq != NULL && (*p)->pDir == NULL) { 
    pAux = *p;
    *p = (*p)->pEsq;
    free(pAux);
    return 1;
    }
    if ((*p)->pDir != NULL && (*p)->pEsq == NULL) { 
    pAux = *p;
    *p = (*p)->pDir;
    free(pAux);
    return 1;
    }
    // no possui dois filhos
    TArvore_Sucessor(*p, &((*p)->pDir));
    // equivalente a TArvore_Antecessor(*p, &((*p)->pEsq));
    return 1;
}


int main(int argc, char const *argv[])
{

    return 0;
}
