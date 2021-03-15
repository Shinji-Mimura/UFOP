## Heap_Binaria.c

Fila de prioridade usando uma Heap Binária

**Definição**

 - Uma Heap permite simular uma árvore binária completa ou quase completa (exceção está no último nível)

- Cada posição do array passa a ser considerdo o "pai" de outras duas posições , chamadas "filhos"

- Posição i é o pai , logo :

- Posição 2*i+1 é o filho da esquerda

- Posição 2*i+2 é o filho da direita

- O pai sempre terá uma prioridade maior ou igual a prioridade do seus filhos

**Custo** :

- Inserção O(log N)

- Remoção O(log N)

- Em ambas verificamoas as violações das propriedas do Heap e se necessário , corrigi-lás

**Inserção :**

- Insiro o elemento no final do array (primeira posição vaga)

- Caminho com o elemento até sua respectiva posição na Heap de acordo com sua prioridade

**Remoção** :

- Remover o elemento do topo da Heap (início do array)

- Copiar elemento do final para o início do array

- Levar elemento do topo da Heap para sua respectiva posição de acordo com sua prioridade

## HeapSort.c

HeapSort ou Ordenação por Heap

**Definição** :

- Heap : Vetor que simula uma arvore binária quase completa

- Todo elemento "pai" do vetor possuir dois elementos "filhos"

- Pai (i) -> Filho (2*i+1) e Filho(2*i+2)

**O HeapSort é recomendado** :

- Para aplicações que não podem tolerar eventualmente um caso desfavorável.

**Não recomendado** :

- Não é recomendado para arquivos com poucos registros, por causa do tempo necessário para construir o heap

**Vantagens** :

- O comportamento do Heapsort é sempre O(n log n), qualquer que seja a entrada

**Desvantagens** :

- O anel interno do algoritmo é bastante complexo se comparado com o do Quicksort

- O Heapsort não é estável

## FP.c

Filhas de Prioridade

**Definição** :

- São um tipo especial de fila que generaliza a ideia de ordenação

- Os elementos agora possuem consigo um dado "Prioridade"

- O valor desta Prioridade determina a posição do elemento na fila , assim como quem deve ser removido primeiro

**Aplicações** :

- Basicamente , problemas que seja preciso de estabelecer prioridades ao acesso de elementos

**Operações** :

- Criar fila

- Inserir elemento na fila com prioridade

- Remoção do elemento com maior prioridade

- Destruição da fila

- Descobrir informações (Lista cheia , vazia e etc...)

**Implementações** :

- Depende da sua aplicação

- Algumas são mais eficientes que outras

**Implementação Estática** :

- Vantagem : Permite utilizar a mesma estrutura da fila

- Desvantagem : Necessita definir o tamanho , com isso pode vir a ocasionar em limitação no número de elementos

**Inserções na Fila de Prioridade através de Array Ordenado** :

- Os elementos na fila são ordenados de forma crescente dentro do Array

- os elementos de maior prioridade estarão no final do Array

- os elementos menor prioridade estarão no início do Array

**Custo** :

- Inserção O(N)

- Remoção O(1)

**Inserção** :

- Precisamos procurar o ponto de inserção de acordo com sua prioridade

- Se caso seja no início ou meio , será necessário mudar os demais elementos do Array de posição

## Pesquisa Sequencial e Binária

**Conceitos básicos** :

- É um estudo de como recuperar informação a partir de uma grande massa de informação já armazenada

- A informação está divida em registros

- Cada registro possui uma chave que será utilizada para pesquisa

- Objetivo da pesquisa : encontrar registros com chaves iguais a chave de pesquisa

**TADS**

- É importante considera-los TADS de tal forma que haja independência em sua implementações

**Operações mais comuns** :

- Inicializar a Estrutura de Dados

- Pesquisar um ou mais registros com determinada chave

- Inserir um novo registro

- Retirar um registro específico

**TAD Dicionário** :

- Inicializa

- Pesquisa

- Insere

- Retira

**Analogias com Dicionário** :

- Chaves -> Palavras

- Registros -> Pronúncia , Definição, Sinônimos e etc...

### Métodos de Pesquisa

**1) Pesquisa Sequencial** :

- Mais simples , procura a partir do primeiro registro até encontrar a chave procurada e então para

- Conjunto armazenado por meio de Array

- Retorna o índice do registro que contém a chave X

- Caso não encontre , retorna -1

- Retorna somente o primeiro registro encontrado , caso tenha registros com chaves iguais , não será útil

- É a melhor escolha para pesquisa em tabelas

**Pesquisa com sucesso** :

- Melho caso : C(n) = 1

- Pior caso : C(n) = n

- Caso médio : C(n) = (n+1) / 2

**Pesquisa sem sucesso** :

- C(n) = n+1

**2) Pesquisa por Busca Binária** :

- Se os registros estiverem em ordem , será mais eficiente a Busca

- Compara a chave que está no registro do meio da tabela e realiza a pergunta

1) Chave menor ? se sim , procura na primeira metade da tabela

2) Chave Maior ? se sim , procura na segunda metade da tabela

- Repete o processo até que se encontre a chave ou constate que não existe

**Análise** :

- A cada interação a tabela é dividida ao meio

- Logo , o número de vezes que é dividido é cerca de log n

- O custo para manter a tabela ordenada é alto

- Não deve ser utilizada em aplicações muito dinâmicas

## Árvore AVL

- O tempo de operações é proporcional aos níveis dela

- É importante mante a árvore com a MENOR quantidade de níveis possíveis , dessa forma otimizando as operações

- O ideal é manter a árvore balanceada
 
**Rotações e Fator de Balanceamento**:
- O Fator de Balanceamento de uma árvore binaria de busca é medido pela subtração dos números de niveis sub-árvore a direita com os da esquerda (FB = R-L)

- O fator de balanceamento deve estar entre -1 <= FB <= 1

- Existem 4 tipos básicos de rotações:

	1) Rotação à esquerda (primitivo)

	2) Rotação à direita (primitivo)

	3) Rotação dupla à esquerda (composto)

	4) Rotação dupla à direita (composto)

**1) Rotação à esquerda (primitivo):**

- O filho da direita se torna a nova raiz

- Raiz original vira o filho da esquerda da nova raiz

* Caso o filho da direita já tenho um filho a esquerda, ele se tornára filho a direita da Raiz Original

- Vai ser usado quando FB > 1 e sub-árvore a direita tem Q

**2) Rotação à direita (primitivo):**

- O filho da esquerda se torna nova raiz

- Raiz original vira filho da direita da nova raiz

* Caso o filho da esquerda já tenho um filho a direita, ele se tornára filho a esquerda da Raiz Original

- Vai ser usado quando FB < 1 e sub-árvore a direita tem Q<=0

**3) Rotação dupla à esquerda (composto):**

- Vai ser usado quando: FB Desequilibrado Positivo (FB > 1) na Raiz Original e sub-árvore à direita com FB Desequilibrado Negativo (FB < 0)

**4) Rotação dupla à direita (composto):**

- Vai ser usado quando: FB Desequilibrado Negativo (FB < -1) na Raiz Original e sub-árvore à esquerda com FB Desequilibrado Positivo (FB > 0)
 
 ## Árvore Binária de Busca

Árvores binárias por definição recursiva, é composta por um único nó raiz , que pode ter nenhum, um ou até no máximo 2 nós filhos que também são árvores binárias

**Regras para inserção de um novo elemento:**

   1) Se ainda não há nó raiz, então o novo elemento será o próprio nó raiz
   2) Se há nó raiz , então compare o novo elemento com o nó raiz:
        caso I) Caso o novo elemento seja menor que o elemento do nó raiz , então o novo elemento é inserido na sub-árvore a da esquerda
        caso II) Caso o novo elemento seja maior o elemento do nó raiz , então o novo elemento é inserido na sub-árvore a da direita
 
. Regras para deletar nó:
    
   1) Caso seja um nó folha , somente deletá-lo 
    2) Caso o nó possua outros nós folhas:
        caso I) Remova o nó folha e coloque o filho da esquerda no lugar
        caso II) Remova o nó folha e coloque o filho da direita no lugar
 
Porém sempre colocaremos no lugar do nó deletado , usaremos o maior elemento da sub-árvore a esquerda ou o menor elemento da sub-árvore a direita , assim mantento a árvore correta
