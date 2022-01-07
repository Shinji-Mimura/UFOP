#include "mmu.hpp"
using namespace std;

int associativo (BlocoMemoria** mem, Endereco *e, int tam){
  for (int i = 0; i < tam; i++){

    if (getEndBlocoBM( mem[i] ) == getEndBloco(e))
      return i;
  }
  return -1;
}

int getLowestCacheHit(BlocoMemoria** cache, int tam){
  int lowest = 999999;
  int position = 0;

  for (int i = 0; i < tam; i++){

    if (lowest > getVezesUsado(cache[i])){
      lowest = getVezesUsado(cache[i]);
      position = i;
    }
  }

  return position;
}

BlocoMemoria *buscarNasMemorias(Endereco *e, BlocoMemoria **ram, BlocoMemoria **cache1, BlocoMemoria **cache2, int tCache1, int tCache2){

		//acesso associativo a memoria
    	int posicaoCache1 = associativo(cache1, e, tCache1);
		int posicaoCache2 = associativo(cache2, e, tCache2);
		int custo =0;


		if (posicaoCache1 != -1){
			custo+=10;

			incVezesUsado(cache1[posicaoCache1]);
			setCusto     (cache1[posicaoCache1],custo);
			setCacheHit  (cache1[posicaoCache1],1);
			setAtualizado(cache1[posicaoCache1]);

			return cache1[posicaoCache1];
		}

     else if(posicaoCache2 != -1){

			int positionLowest1 = getLowestCacheHit(cache1, tCache1);
			custo +=110;
			incVezesUsado(cache2[posicaoCache2]);
			setCusto     (cache2[posicaoCache2],custo);
			setCacheHit  (cache2[posicaoCache2],2);
			setAtualizado(cache2[posicaoCache2]);

			return testaCache1Cache2(positionLowest1, posicaoCache2, cache1, cache2, custo);
		}
		//buscar na ram E O REPASSAR A C2 E DEPOIS A C1
    else{
			custo +=1110;

			int positionLowest1 = getLowestCacheHit(cache1, tCache1);
			int positionLowest2 = getLowestCacheHit(cache2, tCache2);

			if(!isAtualizado(cache2[positionLowest2])){
			  cache2[positionLowest2] = ram[ getEndBloco(e) ];
				incVezesUsado(cache2[positionLowest2]);
				setCacheHit(cache2[positionLowest2],3);
				return testaCache1Cache2(positionLowest1, positionLowest2, cache1, cache2, custo);
			}

      else{
				ram[getEndBlocoBM(cache2[positionLowest2])] = cache2[positionLowest2];
				incVezesUsado(cache2[positionLowest2]);
				setAtualizado(cache2[positionLowest2]);
			  cache2[positionLowest2] = ram[ getEndBloco(e) ];
				setCacheHit  (cache2[positionLowest2],3);
				return testaCache1Cache2(positionLowest1, positionLowest2, cache1, cache2, custo);
			}
		}

}

BlocoMemoria *testaCache1Cache2(int posicaoCache1, int posicaoCache2, BlocoMemoria** cache1, BlocoMemoria** cache2, int custo){
		if(!isAtualizado(cache2[posicaoCache2]))
		cache1[posicaoCache1] = cache2[posicaoCache2];

	  else{
			BlocoMemoria *aux = cache1[posicaoCache1];
			cache1[posicaoCache1] = cache2[posicaoCache2];
			cache2[posicaoCache2] = aux;
		}

		setCusto(cache1[posicaoCache1],custo);

		return cache1[posicaoCache1];
	}
