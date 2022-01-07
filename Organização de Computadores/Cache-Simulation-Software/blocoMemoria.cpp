	#include "blocoMemoria.hpp"
	using namespace std;
	struct blocoMemoria{
			int **palavras = new int*[4];
			int endBloco;
			bool atualizado;
			int custo;
			int cacheHit;
			int VezesUsado;
	};

	BlocoMemoria* gerarBM(){
		BlocoMemoria * aux = new BlocoMemoria;
		aux->palavras[0] = gerarInt();
		aux->palavras[1] = gerarInt();
		aux->palavras[2] = gerarInt();
		aux->palavras[3] = gerarInt();
		aux->endBloco 	= -1;
		aux->atualizado = false;
		aux->custo 		= 0;
		aux->cacheHit 	= 0;
		aux->VezesUsado = 0;
		return aux;
	}

	int* gerarInt(){
		int * aux = new int;
		*aux = rand() % 4;
		return aux;
	}

	void deleteInt(int** palavra){
		delete &palavra[0];
		delete &palavra[1];
		delete &palavra[2];
		delete &palavra[3];
		delete[] palavra;
	}


	void deleteBM(BlocoMemoria **a, int tam){
		for(int i=tam-1; i>=0; i--){
			deleteInt(a[i]->palavras);
			delete[] a[i];
		}
		delete[] a;
	}

	int getCusto(BlocoMemoria *c) {
		return c->custo;
	}

	void setCusto(BlocoMemoria *c, int custo) {
		c->custo = custo;
	}

	int** getPalavras(BlocoMemoria * c) {
			return c->palavras;
	}

	int getPalavra (BlocoMemoria* palavras, int palavra){
		return *palavras->palavras[palavra];
	}

	void setPalavras(BlocoMemoria* c, int** palavras) {
		c->palavras = palavras;
	}

	void setPalavra(BlocoMemoria* c, int i, int* palavras) {
		c->palavras[i] = palavras;
	}

	int getEndBlocoBM(BlocoMemoria *c) {
		return c->endBloco;
	}

	void setEndBlocoBM(BlocoMemoria *c, int endBloco) {
		c->endBloco = endBloco;
	}

	bool isAtualizado(BlocoMemoria *c) {
		return c->atualizado;
	}

	void setAtualizado(BlocoMemoria *c) {
		c->atualizado = !c->atualizado;
	}
	void setAtualizado(BlocoMemoria *c, bool d) {
		c->atualizado = d;
	}

	int getCacheHit(BlocoMemoria *c) {
		return c->cacheHit;
	}

	void setCacheHit(BlocoMemoria *c, int cacheHit) {
		c->cacheHit = cacheHit;
	}

	int getVezesUsado(BlocoMemoria * mem){
		return mem->VezesUsado;
	}

	void incVezesUsado(BlocoMemoria * mem){
		mem->VezesUsado++;
	}
