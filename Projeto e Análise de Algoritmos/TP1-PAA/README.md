## Trabalho Prático I - PAA (Projeto e Análise de Algoritmos)

Este repositório contém um projeto prático relacionado à disciplina de Projeto e Análise de Algoritmos. O foco principal do projeto é a implementação e análise de três algoritmos de ordenação: Insertion Sort, Merge Sort e Radix Sort.

### Trabalho Prático I - PAA
**Integrantes:**
- Lucas Araújo
- Fabio Henrique
- Lorrayne

**Data de Entrega:** 12/06/2023 - 12:00h

### Códigos dos Algoritmos:

1. **Insertion Sort**:
   - [Código do Insertion Sort](https://github.com/Shinji-Mimura/TP1-PAA/blob/main/src/InsertionSort.c)
   - Análise de Complexidade:
     - Melhor Caso: O(n)
     - Pior Caso: O(n²)
     - Caso Médio: O(n²)

2. **Merge Sort**:
   - [Código do Merge Sort](https://github.com/Shinji-Mimura/TP1-PAA/blob/main/src/MergeSort.c)
   - Análise de Complexidade:
     - A função 'merge' tem uma complexidade de tempo O(n).
     - A função 'mergesort' implementa uma estratégia de divisão e conquista, resultando em uma complexidade de tempo O(n log n).

3. **Radix Sort**:
   - [Código do Radix Sort](https://github.com/Shinji-Mimura/TP1-PAA/blob/main/src/RadixSort.c)
   - Análise de Complexidade:
     - Melhor Caso: Omega(n + k)
     - Pior Caso: O(n + k)
     - Caso Médio: Theta(n + k)

4. **Main**:
   - [Código Principal](https://github.com/Shinji-Mimura/TP1-PAA/blob/main/src/main.c)
   - Este código é responsável por executar os algoritmos de ordenação com base na opção fornecida e calcular o tempo médio de execução para diferentes instâncias.
