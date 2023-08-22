/*

* Lucas de Araújo - 18.2.4049

*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// Função para encontrar o máximo de dois números
int max(int a, int b){
    return (a > b) ? a : b;
}

// Função para retornar a maior subsequência palíndromo em str
int lps(char* str){
    int n = strlen(str);
    int i, j, cl;
    int L[n][n];

    // Strings de tamanho 1 são palíndromos
    for(i = 0; i < n; i++)
        L[i][i] = 1;

    // Para substrings de tamanho 2 a n
    for(cl = 2; cl <= n; cl++){
        for(i = 0; i < n - cl + 1; i++){
            j = i + cl - 1;
            if(str[i] == str[j] && cl == 2)
                L[i][j] = 2;
            else if(str[i] == str[j])
                L[i][j] = L[i+1][j-1] + 2;
            else
                L[i][j] = max(L[i][j-1], L[i+1][j]);
        }
    }

    return L[0][n-1];
}

int main() {
    char *seq = NULL;
    size_t len = 0;
    size_t read;

    printf("Por favor, digite uma sequência de caracteres:\n");
    read = getline(&seq, &len, stdin);

    if (read == -1) {
        printf("Falha ao ler a sequência de entrada.\n");
        return 1;
    }

    // Removendo o caractere de nova linha inserido por getline() quando você pressiona Enter
    if (read > 0 && seq[read-1] == '\n')
        seq[read-1] = '\0';

    printf("O tamanho da LPS é %d\n", lps(seq));

    free(seq);  
    return 0;
}
