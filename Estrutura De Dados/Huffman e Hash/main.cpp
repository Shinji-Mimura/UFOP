#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "TabelaHash.hpp"
#include "huffman.hpp"

int main(int argc, char const *argv[]){
  char menu;
  printf("Qual questão deseja ver ? (a/b|'s' para sair)\n");
  cin>>menu;
  while(menu!='s'){
    switch (menu) {
      case 'a':
        A();
        break;
      case 'b':
        B();
        break;
      default:
        cout<<"Questao nao existe, tente novamente"<<endl;
    }
    printf("Qual questão deseja ver ? (a/b|'s' para sair)\n");
    cin>>menu;
  }
return 0;
}
