// Lucas de Araújo - 18.2.4049

/*

- A análise de complexidade será feita sobre a função 'power' visto que é nela que ocorre a recursividade.
- Primeiramente foi realizada a analise sobre cada linha da função 'power' e das funções que ela invoca. 
- As análises estão feitas em cada uma das linhas no próprio código em forma de comentário
- Função inicial: T(n) = T(n/2) + 19
- Pela relação de recorrência, temos: T(n) = T(n/(2^k)) - 19k
- O caso base será quando n/(2^k) = 1 => ln(n)
- Substituindo: T(n) = T(1) - 19 * ln(n) => T(n) = O(1) - O(19*ln(n)) => O(ln(n))
- Portanto, este algoritmo possui complexidade de O(ln(n))

*/

#include <stdio.h>

/* função que retorna o número na posição escolhida */
int fib(int n)
{
    int F[2][2] = {{1, 1}, {1, 0}};
    if (n == 0)
        return 0;
    power(F, n - 1);
    return F[0][0];
}

void power(int F[2][2], int n) // T(n/2) + 19
{
    if (n == 0 || n == 1) { // 1
        return;
    }
    
    int M[2][2] = {{1, 1}, {1, 0}}; // 1

    power(F, n / 2); // T(n/2)
    multiply(F, F); // 8

    if (n % 2 != 0) // 1
        multiply(F, M); // 8
}

void multiply(int F[2][2], int M[2][2]) // 8 no total
{
    int x = F[0][0] * M[0][0] + F[0][1] * M[1][0]; // 1
    int y = F[0][0] * M[0][1] + F[0][1] * M[1][1]; // 1
    int z = F[1][0] * M[0][0] + F[1][1] * M[1][0]; // 1
    int w = F[1][0] * M[0][1] + F[1][1] * M[1][1]; // 1

    F[0][0] = x; // 1
    F[0][1] = y; // 1
    F[1][0] = z; // 1
    F[1][1] = w; // 1
}

int main()
{
    int n;
    printf("Enter the position n: ");
    scanf("%d", &n);
    printf("Fibonacci number at position %d is: %d \n", n, fib(n));
    return 0;
}
