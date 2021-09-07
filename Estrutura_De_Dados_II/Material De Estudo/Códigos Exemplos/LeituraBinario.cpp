#include<iostream>
#include<stdio.h>


using namespace std;

typedef struct 
{
    char titulo[30];
    int codlivro;
    float preco;
} reglivro;

int main(int argc, char const *argv[])
{
    FILE *arq;
    reglivro livro;
    if ((arq = fopen("livros.bin", "rb")) == NULL)
    {
        cout << "Erro na abertura \n";
        return 0;
    }

    while(fread(&livro, sizeof(livro), 1, arq) == 1) {
        cout << livro.titulo << endl;
        cout << livro.codlivro << endl;
        cout << livro.preco << endl;
    }

    fclose(arq);
    
    return 0;
}

