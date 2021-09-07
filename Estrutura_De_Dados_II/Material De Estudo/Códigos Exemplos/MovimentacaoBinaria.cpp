#include <iostream>
#include <stdio.h>
#include <stdlib.h>

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
    long desloc;

    if (argc != 3)
    {
        cout << "Formato: Executavel - Arquivo - Registro" << endl;
        exit(1);
    }

    if ((arq = fopen(argv[1], "rb")) == NULL)
    {
        cout << "Erro na abertura do arquivo" << endl;
        exit(1);
    }

    desloc = atoi(argv[2]) * sizeof(livro);

    if (fseek(arq, desloc, 0) != 0)
    {
        cout << "Movimentação não realizada" << endl;
        exit(1);
    }

    if (fread(&livro, sizeof(livro), 1, arq) != 1)
    {
        cout << "Leitura não realizada" << endl;
        exit(1);
    }

    cout << livro.titulo << " " << livro.codlivro << " " << livro.preco << endl;

    fclose(arq);

    return 0;
}
