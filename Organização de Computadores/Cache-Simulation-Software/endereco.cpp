	#include "endereco.hpp"
using namespace std;
struct endereco {
int endBloco;
int endPalavra;
};

Endereco * gerarEnd(){
	Endereco * aux = new Endereco;
	aux->endBloco = -1;
	aux->endPalavra = -1;
	return aux;
}


void deleteEnd(Endereco *a){
	delete[] a;
}

int getEndBloco(Endereco *c) {
	return c->endBloco;
}

void setEndBloco(Endereco *c, int endBloco) {
	c->endBloco = endBloco;
}

int getEndPalavra(Endereco *c) {
	return c->endPalavra;
}

void setEndPalavra(Endereco *c, int endPalavra) {
	c->endPalavra = endPalavra;
}
