#pragma once
#include <iostream>
#include <bits/stdc++.h>

typedef struct blocoMemoria BlocoMemoria;

BlocoMemoria * gerarBM();

int* gerarInt();
void deleteInt(int** palavra);

void deleteBM(BlocoMemoria** a, int tam);

int getCusto(BlocoMemoria *c);
void setCusto(BlocoMemoria *c, int custo);

int** getPalavras(BlocoMemoria *c);
int getPalavra(BlocoMemoria* palavras, int palavra);

void setPalavras(BlocoMemoria* c, int** palavras);
void setPalavra(BlocoMemoria* c, int i, int* palavras);

int getEndBlocoBM(BlocoMemoria *c);
void setEndBlocoBM(BlocoMemoria *c, int endBloco);
bool isAtualizado(BlocoMemoria *c);

void setAtualizado(BlocoMemoria *c);
void setAtualizado(BlocoMemoria *c, bool d);

int getCacheHit(BlocoMemoria *c);
void setCacheHit(BlocoMemoria *c, int cacheHit);

int getVezesUsado(BlocoMemoria * mem);
void incVezesUsado(BlocoMemoria * mem);
