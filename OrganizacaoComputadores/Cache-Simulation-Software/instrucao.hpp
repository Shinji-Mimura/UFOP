#pragma once
#include <iostream>
#include <bits/stdc++.h>
#include "endereco.hpp"

typedef struct instrucao Instrucao;

Instrucao * gerarInst();

void gerarEndInst(Instrucao* inst);

void deleteInst(Instrucao** a, int tam);

Endereco *getAdd1(Instrucao *c);

void setAdd1(Instrucao *c, Endereco *add1);

Endereco *getAdd2(Instrucao *c);

void setAdd2(Instrucao *c, Endereco *add2);

Endereco *getAdd3(Instrucao *c);

void setAdd3(Instrucao *c, Endereco *add3);

int getOpcode(Instrucao *c);

void setOpcode(Instrucao *c, int opcode);
