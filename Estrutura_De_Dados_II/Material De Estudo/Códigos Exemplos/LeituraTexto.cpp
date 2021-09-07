#include <iostream>
#include <stdio.h>

using namespace std;

int main(int argc, char const *argv[])
{
    FILE *arq;
    char ch;

    if ((arq = fopen("teste.txt","r")) == NULL){ // comparação para descobrir se a abertura do arquivo ocorreu com sucesso ou não
        cout << "Erro na abertura\n";
    }

    ch = getc(arq); // lê o primeiro caractere do arq
    while (ch != EOF) // vare o arquivo
    {
        putchar(ch); //imprime na tela o caractere lido
        ch = getc(arq); // le o proximo caractere
    }

    fclose (arq); // fecha o arquivo

    return 0;
}
