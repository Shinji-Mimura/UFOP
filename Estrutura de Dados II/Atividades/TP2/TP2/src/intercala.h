#ifndef INTERCALA_H
#define INTERCALA_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "estatistica.h"
#include "aluno.h"
#include "fitas.h"

/* Protótipo das Funções de Intercalação */
void intercala2F(FILE *, int, Estatisticas *est);
void criaBlocosIntercalacao(FILE *, Fita *, int, Estatisticas *est);
int intercala(Fita *, Fita *, Aluno *, int, Estatisticas *est);

#endif