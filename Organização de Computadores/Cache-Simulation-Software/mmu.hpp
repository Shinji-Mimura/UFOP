#pragma once
#include <iostream>
#include <bits/stdc++.h>
#include "endereco.hpp"
#include "instrucao.hpp"
#include "blocoMemoria.hpp"

int associativo (BlocoMemoria** mem, Endereco e, int tam);
int getLowestCacheHit(BlocoMemoria** cache, int tam);
BlocoMemoria *buscarNasMemorias(Endereco *e, BlocoMemoria **ram, BlocoMemoria **cache1, BlocoMemoria **cache2, int tCache1, int tCache2);
BlocoMemoria *testaCache1Cache2(int posicaoCache1, int posicaoCache2, BlocoMemoria** cache1, BlocoMemoria** cache2, int custo);
