#pragma once
#include <iostream>
#include <bits/stdc++.h>
#include "endereco.hpp"
#include "instrucao.hpp"
#include "blocoMemoria.hpp"
#include "mmu.hpp"
using namespace std;
void montarRam(BlocoMemoria** ram, int tamanhoRam, int qdePalavrasBloco);

void montarCacheVazia(int tamanho, BlocoMemoria** cache);

void carregarInstrucoesTXT(Instrucao** memoriaInstrucoes);

void maquina(Instrucao** memoriaInstrucoes, BlocoMemoria** ram, BlocoMemoria** cache1, BlocoMemoria** cache2, int tCache1, int tCache2);
