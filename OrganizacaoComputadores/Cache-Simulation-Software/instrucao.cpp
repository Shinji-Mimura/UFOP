#include "instrucao.hpp"
using namespace std;
struct instrucao {
	 Endereco *add1;
	 Endereco *add2;
	 Endereco *add3;
	 int opcode;
};

Instrucao * gerarInst(){
	Instrucao * aux = new Instrucao;
	aux->add1 = gerarEnd();
	aux->add2 = gerarEnd();
	aux->add3 = gerarEnd();
	aux->opcode = -1;
	return aux;
}

void deleteInst(Instrucao **a, int tam){
	for(int i=tam-1; i>=0; i--){
		deleteEnd(a[i]->add1);
		deleteEnd(a[i]->add2);
		deleteEnd(a[i]->add3);
		delete[] a[i];
	}
	delete[] a;
}

Endereco *getAdd1(Instrucao *c) {
	return c->add1;
}

void setAdd1(Instrucao *c, Endereco *add1) {
	c->add1 = add1;
}

Endereco *getAdd2(Instrucao *c) {
	return c->add2;
}

void setAdd2(Instrucao *c, Endereco *add2) {
	c->add2 = add2;
}

Endereco *getAdd3(Instrucao *c) {
	return c->add3;
}

void setAdd3(Instrucao *c, Endereco *add3) {
	c->add3 = add3;
}

int getOpcode(Instrucao *c) {
	return c->opcode;
}

void setOpcode(Instrucao *c, int opcode) {
	c->opcode = opcode;
}
