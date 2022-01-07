#include "maquina.hpp"

void montarRam(BlocoMemoria** ram, int tamanhoRam, int qdePalavrasBloco){

	for(int i=0; i<tamanhoRam; i++){
		BlocoMemoria *aux = gerarBM();
		setEndBlocoBM(aux, i);
		int** palavras = new int*[qdePalavrasBloco]; //cria blocos aux com palavras que serão postos na ram


		for(int j=0;j<qdePalavrasBloco; j++){
			int * intaux = new int;
			*intaux = rand() % 100;
			palavras[j] = intaux;
		}

		setPalavras(aux, palavras);
		ram[i]= aux;

	}
}

void montarCacheVazia(int tamanho, BlocoMemoria** cache){
	for(int i=0; i<tamanho; i++){
		BlocoMemoria *aux = gerarBM();
		//forcando cache estar vazia
		setEndBlocoBM(aux, 0);

		 cache[i]= aux;
		// delete[] aux;
	}
}

void carregarInstrucoesTXT(Instrucao** memoriaInstrucoes){

	ifstream inFile;
	inFile.open("./instrucoes.txt");

	if(!inFile){
		cerr<< "nao foi capaz de encontrar instrucoes.txt";
		exit(1);
	}
	int opcode=0, i=0;
	while(opcode!=-1){
		int endBloco;
		int endPalavra;

		inFile>>opcode;
		inFile>>endBloco;
		inFile>>endPalavra;

		setOpcode(memoriaInstrucoes[i], opcode);
		setEndBloco(getAdd1(memoriaInstrucoes[i]), endBloco);
		setEndPalavra(getAdd1(memoriaInstrucoes[i]), endPalavra);

		inFile>>endBloco;
		inFile>>endPalavra;

		setEndBloco(getAdd2(memoriaInstrucoes[i]), endBloco);
		setEndPalavra(getAdd2(memoriaInstrucoes[i]), endPalavra);

		inFile>>endBloco;
		inFile>>endPalavra;

		setEndBloco(getAdd3(memoriaInstrucoes[i]), endBloco);
		setEndPalavra(getAdd3(memoriaInstrucoes[i]), endPalavra);

		i++;
	}

	inFile.close();

}

void maquina(Instrucao** memoriaInstrucoes, BlocoMemoria** ram, BlocoMemoria** cache1, BlocoMemoria** cache2, int tCache1, int tCache2){
	//registradores
	int pc = 1;
	int custo=0;
	//caches 1 e 2 Hit e miss
	int missC1 = 0;
	int hitC1 = 0;
	int missC2 = 0;
	int hitC2 = 0;

	for(int i=0; getOpcode(memoriaInstrucoes[i])!=-1; i++){
		//TP2
		if(getOpcode(memoriaInstrucoes[i])!=-1){

			BlocoMemoria *dadoMemoriaAdd1= gerarBM();
			dadoMemoriaAdd1 = buscarNasMemorias(getAdd1(memoriaInstrucoes[i]), ram, cache1, cache2, tCache1, tCache2);

			BlocoMemoria *dadoMemoriaAdd2= gerarBM();
			dadoMemoriaAdd2 = buscarNasMemorias(getAdd2(memoriaInstrucoes[i]), ram, cache1, cache2, tCache1, tCache2);

			BlocoMemoria *dadoMemoriaAdd3= gerarBM();
			dadoMemoriaAdd3 = buscarNasMemorias(getAdd3(memoriaInstrucoes[i]), ram, cache1, cache2, tCache1, tCache2);

			//incrementando custos
			custo += getCusto(dadoMemoriaAdd1);
			custo += getCusto(dadoMemoriaAdd2);
			custo += getCusto(dadoMemoriaAdd3);

			 //validando hits e misses

			if(getCacheHit(dadoMemoriaAdd1)==1){
				hitC1++;
			}

			else if(getCacheHit(dadoMemoriaAdd1)==2){
				missC1++;
				hitC2++;
			}

			else if(getCacheHit(dadoMemoriaAdd1)==3){
				missC1++;
				missC2++;
			}

			//////////////////

			if(getCacheHit(dadoMemoriaAdd2)==1){
				hitC1++;
			}

			else if(getCacheHit(dadoMemoriaAdd2)==2){
				missC1++;
				hitC2++;
			}

			else if(getCacheHit(dadoMemoriaAdd2)==3){
				missC1++;
				missC2++;
			}

			//////////////////////
			if(getCacheHit(dadoMemoriaAdd3)==1){
				hitC1++;
			}

			else if(getCacheHit(dadoMemoriaAdd3)==2){
				missC1++;
				hitC2++;
			}

			else if(getCacheHit(dadoMemoriaAdd3)==3){
				missC1++;
				missC2++;
			}

			switch (getOpcode(memoriaInstrucoes[i])){
				//levar para cache1 dados externos
				case 0:{
					//cout<<"Nao ha demanda por levar dados externos para as memorias. "<<endl;
					break;
				}
				case 1:{
					//somar
					int conteudo1 = getPalavra(dadoMemoriaAdd1, getEndPalavra(getAdd1(memoriaInstrucoes[i])));
					int conteudo2 = getPalavra(dadoMemoriaAdd2, getEndPalavra(getAdd2(memoriaInstrucoes[i])));
					int soma = conteudo1+conteudo2;
					//salvando resultado na cache1
					setPalavra(dadoMemoriaAdd3, getEndPalavra(getAdd3(memoriaInstrucoes[i])), &soma);

					break;
				}
				case 2:{
					//subtrair
					int conteudo1 = getPalavra(dadoMemoriaAdd1, getEndPalavra(getAdd1(memoriaInstrucoes[i])));
					int conteudo2 = getPalavra(dadoMemoriaAdd2, getEndPalavra(getAdd2(memoriaInstrucoes[i])));
					int sub = conteudo1-conteudo2;

					//salvando resultado na cache1
					setPalavra(dadoMemoriaAdd3, getEndPalavra(getAdd3(memoriaInstrucoes[i])), &sub);

					break;
				}
			}

			pc++;

			// deleteBM(dadoMemoriaAdd1);
			// deleteBM(dadoMemoriaAdd2);
			// deleteBM(dadoMemoriaAdd3);

		}//end if
	}//end for
	cout<<"\n\n----------------------------------------------------"<<endl;
	cout<<"Custo total do programa: "<<custo<<endl;
	cout<<"Hits e Misses do programa - C1 hit "<<hitC1<<" ("<<hitC1/((hitC1+missC1)/100)<<"%) | "<<" C1 miss "<<missC1<<" | "<<" C2 hit "<<hitC2<<" ("<<hitC2/((hitC2+missC2)/100)<<"%) | "<<" C2 miss: "<<missC2<<endl;
	cout<<"----------------------------------------------------"<<endl;
	cout<<"---------------------\nRAM:\t 8192"<<endl<<"Cache 1: "<<tCache1<<endl<<"Cache 2: "<<tCache2<<endl<<"---------------------"<<endl;

}
