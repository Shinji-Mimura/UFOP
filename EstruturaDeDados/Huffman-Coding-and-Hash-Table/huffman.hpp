#pragma once
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
typedef struct minimo Minimo;
typedef struct heap Heap;

//Protótipos///////////////////////////////////////////

Minimo* cria_no(char caracter, unsigned freq);
Heap* cria_heap(unsigned capacity);
void troca_no(Minimo** a, Minimo** b);
void heapificar(Heap* heapmin, int idx);
int tam_um(Heap* heapmin);
Minimo* extrai_menor(Heap* heapmin);
void insere_heap(Heap* heapmin, Minimo* no);
void cria_heap_minimo(Heap* heapmin);
void imprime(int arr[], int n);
int check_folha(Minimo* root);
Heap* constroi(char data[], int freq[],int size);
Minimo* arvore_huffman(char data[], int freq[], int size);
void imprime_codigo(Minimo* root, int arr[], int cima);
void huffman_cod(string &data, int freq[], int size);
int sweep(string &arr, int &freq);

//SETs & GETs//////////////////////////////////////////

char getSimb(Minimo *a);
unsigned getFreq(Minimo *a);
unsigned getSize(Heap *a);
unsigned getCapacity(Heap *a);
void setSimb(Minimo *a, char b);
void setFreq(Minimo *a, unsigned b);
void setSize(Heap *a, unsigned b);
void setCapacity(Heap *a, unsigned b);

void A();
