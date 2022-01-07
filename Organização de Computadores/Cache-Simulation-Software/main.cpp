#include <iostream>
#include <bits/stdc++.h>
#include "endereco.hpp"
#include "instrucao.hpp"
#include "blocoMemoria.hpp"
#include "mmu.hpp"
#include "maquina.hpp"

using namespace std;

int main(int argc, char const *argv[]){
			int tamanhoRam;

			int tamanhoCache1;
			int tamanhoCache2;

			int tamanhoPrograma;
			int qdePalavrasBloco;
			int menu = 0;
			bool devmode = 0;

			cout<<"\t\t\t\t\t======================"<<endl;
			cout<<"\t\t\t\t\t||SIMULADOR DE CACHE||"<<endl;
			cout<<"\t\t\t\t\t======================"<<endl;
			
	while(menu!=-1){
		cout<<endl<<"\t\t\t\t\t||=======MENU=======||"<<endl;
		cout<<"| -1 Para Sair |::| 0 Para Configurar variaveis da cache |::| 1 Para Carregar Valores Default |"<<endl;
		cout<<"\nOpcao: ";
		cin>>menu;
		if(menu==404){

			menu = 0;
			devmode = true;
			cout<<endl<<"\t\t\t\t\tModo desenvolvedor: "<<endl;

		}
		switch(menu){

			case 0:{
				cout<<"\nTamanho da Cache 1<--------------->(default: 2048):";
				cin>>tamanhoCache1;
				cout<<"Tamanho da Cache 2<--------------->(default: 4096):";
				cin>>tamanhoCache2;
				tamanhoPrograma = 49984;
				qdePalavrasBloco = 4;
				tamanhoRam= 8192;

				if(devmode){

					cout<<"Tamanho da RAM<------------------->(NAO RECOMENDADO MUDAR default: 8192):";
					cin>>tamanhoRam;
					cout<<"Tamanho do programa<-------------->(NAO RECOMENDADO MUDAR default: 49984):";
					cin>>tamanhoPrograma;
					cout<<"Quantidade de Palavras no Bloco<-->(NAO RECOMENDADO MUDAR default: 4):";
					cin>>qdePalavrasBloco;

				}
				break;

			}

			default:{

				tamanhoRam= 8192;

				tamanhoCache1 = 2048;
				tamanhoCache2 = 4096;

				tamanhoPrograma = 49984;
				qdePalavrasBloco = 4;

				break;
			}

		}
		if(menu!=-1){
			Instrucao **memoriaInstrucoes = new Instrucao*[tamanhoPrograma];

			for(int i=0; i<tamanhoPrograma; i++){
				memoriaInstrucoes[i] = gerarInst(); //Vetor com 3 posições de instruções e -1 para halt
			}

			BlocoMemoria **ram = new BlocoMemoria*[tamanhoRam]; //Memória principal
			for(int i=0; i<tamanhoRam; i++){
				ram[i] = gerarBM();
			}

			BlocoMemoria **cache1 = new BlocoMemoria*[tamanhoCache1]; //Cache 1
				for(int i=0; i<tamanhoCache1; i++){
					cache1[i] = gerarBM();
				}

			BlocoMemoria **cache2 = new BlocoMemoria*[tamanhoCache2]; //Cache 2
			for(int i=0; i<tamanhoCache1; i++){
				cache2[i] = gerarBM();
			}


					montarRam(ram, tamanhoRam, qdePalavrasBloco);
					montarCacheVazia(tamanhoCache1, cache1);
					montarCacheVazia(tamanhoCache2, cache2);
					carregarInstrucoesTXT(memoriaInstrucoes);

					maquina(memoriaInstrucoes, ram, cache1, cache2, tamanhoCache1, tamanhoCache2);

					cout<<"terminou\n";
				cout<<"---------------------"<<endl<<endl;
		}
	}

	return 0;
}
