#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct aluno Aluno;
typedef struct hash Hash;

//Protótipos////////////////

Hash* cria(int tam_tabela);
void libera(Hash* ha);
int valorString(char *str);
int insere(Hash* ha, Aluno al); //sem colisão
int busca(Hash* ha, int mat, Aluno al); // sem colisão
int insere_endAberto(Hash* ha, Aluno al); // com colisão
int busca_endAberto(Hash* ha, int mat, Aluno* al); // com colisão
int chaveDivisao(int chave, int tam_tabela);
int chaveMultiplicacao(int chave, int tam_tabela);
int chaveDobra(int chave, int tam_tabela);
int sondagem_linear(int pos, int i, int tam_tabela);
int sondagem_quadratica(int pos, int i, int tam_tabela);
int duploHash(int H1, int chave, int i, int tam_tabela);
void B();
