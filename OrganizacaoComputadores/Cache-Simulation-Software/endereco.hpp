#pragma once
#include <iostream>
#include <bits/stdc++.h>

typedef struct endereco Endereco;

Endereco * gerarEnd(int q);
Endereco * gerarEnd();

void deleteEnd(Endereco *a);

void juntarEnd(Endereco* a, Endereco* b, int i);

int getEndBloco(Endereco *c);

void setEndBloco(Endereco *c, int endBloco);

int getEndPalavra(Endereco *c);

void setEndPalavra(Endereco *c, int endPalavra);
