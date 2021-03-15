Prelúdio
--------

Neste capítulo nos é apresentado a familia de linguagens `Lisp`,
concebida por McCarthy em 1960 e, que tem como proposta poder ter
funções matemáticas para montar sua estruturas de dados.

Lisp no começo não possui tanta eficiência em computações numéricas por
conta de seu caráter experimental. Após anos de aperfeiçoamento, Lisp
foi se popularizando e hoje é bem presente em meios como a `shell` dos
sistemas operacionais, meios estes que não tem como preocupação central
o parâmetro de eficiência.

Lisp é ótima para o estudo de
estrutura de dados e suas relações.

Elementos da Programação 
------------------------

Linguagens podem servir de frameworks para organizar nossas ideias a
respeito de processos, toda linguagem poderosa tem três mecanismos que
permitem isto

-   **Expressões Primitivas**

    Entidades mais simples que a linguagem procura se preocupar

-   **Meios de Combinação**

    Forma pela qual elementos compostos são construídos através de
    elementos mais simples

-   **Meios de Abstração**

    Formas pela qual elementos compostos são manipulados como unidades

Combinações 
-----------

As combinações são feito de forma recursiva, com operador mais a
esquerda e sempre executando as operações mais internas da expressão

Considere o seguinte trecho de código:

``` {.Scheme language="Scheme"}
(* (+ 2 (* 4 6)) (+ 3 5 7))
```

A regra de avaliação será aplicada a quatro operações através de
recursão. A recursão é uma técnica poderosa para lidar com os objetos e
suas respectivas hierarquias, tendo em vista isso, as operações podem
ser escritas na seguinte ordem

1.  \* 4 6 = 24

    1.  *Estas duas expressões estão no mesmo nível de hierarquia*

    2.  \+ 2 24 = 26

    3.  \+ 3 5 7 = 15

2.  \* 26 15 = 390

Modelo de Substituição
----------------------

No processo realizado pelo modelo de substituição, você substitui cada
parâmetro formal no corpo da expressão pelo valor do argumento
correspondente

Podemos ilustrar isto da seguinte forma, considere a expressão a seguir:

``` {.Scheme language="Scheme"}
(define (sum-of-squares x y)  
     (+ (square x) (square y)))
     (define (square x) (* x x))
```

Chamaremos a função da seguinte forma : `(sum-of-squares 3 4)`

1.  Nós temos um parâmetro formal, `x`, que é chamado como argumento 3 e
    `y`, que é chamado como argumento 4

2.  Agora cada ocorrência de `x` e `y` no corpo da equação será
    substituído respectivamente por 3 e 4

3.  O corpo da equação então terá esta aparência:
    `(+ (square 3) (square 4))`

4.  Usando a definição de `square`, isto se torna: `(+ (* 3 3) (* 4 4))`

5.  Aplicando a multiplicação em ambos, temos: `(+ 9 16)`

6.  Aplicamos a soma e no final teremos 25 como resultado

O objetivo da substituição é nos ajudar a pensar sobre a aplicação do
procedimento e não fornecer uma descrição precisa de como o intérprete
realmente funciona. Os intérpretes típicos não avaliam as aplicações do
procedimento manipulando o texto para substituir valores dos parâmetros
formais

Procedures e Processos 
----------------------

Um procedimento é um padrão para a evolução local de um processo
computacional. Ele especifica como cada estágio do processo é construído
sobre o estágio anterior. É desejável poder fazer declarações sobre o
comportamento geral, ou global, de um processo cuja evolução local foi
especificada por um procedimento, porém, isso é muito difícil de fazer
em geral, mas podemos pelo menos tentar descrever alguns padrões típicos
de evolução do processo.

Recursão e Iteração 
-------------------

A teoria da técnica de `recursão` já foi apresentada anteriormente,
porém nesta seção irei aprofundar um pouco mais sobre ela através de
outros exemplos. Considere o exemplo abaixo:

``` {.Scheme language="Scheme"}
(define (factorial n)
  (if (= n 1) 
      1 
      (* n (factorial (- n 1)))))
```

Utilizando do modelo de substituição também já mencionado, podemos
ilustrar a execução deste código da seguinte maneira:

``` {.Scheme language="Scheme"}
(factorial 6)
(* 6 (factorial 5))
(* 6 (* 5 (factorial 4)))
(* 6 (* 5 (* 4 (factorial 3))))
(* 6 (* 5 (* 4 (* 3 (factorial 2)))))
(* 6 (* 5 (* 4 (* 3 (* 2 (factorial 1))))))
(* 6 (* 5 (* 4 (* 3 (* 2 1)))))
(* 6 (* 5 (* 4 (* 3 2))))
(* 6 (* 5 (* 4 6)))
(* 6 (* 5 24))
(* 6 120)

> 720 
```

Porém, seria possível pensar em executar esta mesma operação de
fatoração de outra maneira, vamos conferir este mesmo procedimento
através da técnica de `iteração`. Considere o código abaixo:

``` {.Scheme language="Scheme"}
(define (factorial n) 
  (fact-iter 1 1 n))

(define (fact-iter product counter max-count)
  (if (> counter max-count)
      product
      (fact-iter (* counter product)
                 (+ counter 1)
                 max-count)))
```

Neste código, a cada iteração realizada pelo código (ou seja, a cada
chamada de `fact-iter`) é feita uma comparação no if, caso o `counter`
seja maior que `max-count` significa então que o código já fez o número
de iterações necessárias e deve retornar o produto (o `product` e
`counter` são inicializados com o valor 1). Caso a comparação no if seja
falsa, é chamada novamente a função `fact-iter`, porém com o parâmetro
`product` agora sendo `product*counter` e é acrescentado uma unidade em
`counter`

Para facilitar o entendimento, aqui está uma visualização do processo:

``` {.Scheme language="Scheme"}
(factorial 6)
(fact-iter 1 1 6)
(fact-iter 1 2 6)
(fact-iter 2 3 6)
(fact-iter 6 4 6)
(fact-iter 24 5 6)
(fact-iter 120 6 6)
(fact-iter 720 7 6)

> 720
```

Em geral, um processo iterativo é aquele cujo o estado pode ser resumido
por um número fixo de variáveis de estado, junto com uma regra fixa que
faz com que as variáveis de estado devam ser atualizadas conforme o
processo ocorrer de um estado para outro e um teste final (caso base)
que especifica as condições sob quais quais o processo deve encerrar

Apesar de ambos processos computarem a mesma função, eles possuem uma
diferença, o da curva do processo

Tipos de Recursão
-----------------

As recursões mencionadas podem ser resumidas e categorizadas da seguinte
forma:

-   **Recursão Linear**

    o comprimento da cadeia de operações realizadas e, portanto, a
    quantidade de informação necessária para mantê-la sob controle,
    cresce linearmente com `n` (é proporcional a n), assim como o número
    de etapas. Esse processo é chamado de processo recursivo linear.

-   **Recursão em Árvore**

    Em geral, o número de passos requiridos para a execução de uma
    árvore recursiva será proporcional ao número de nós da árvore,
    enquanto o espaço será proporcional à altura da árvore. O processo
    de recursão em árvore pode ser uma ferramenta natural e poderosa.

Ordem de Grandeza
-----------------

A noção de ordem de crescimento é útil para se obter uma medida dos
recursos exigidos por um processo, principalmente a medida que os
valores de entrada se tornam maiores. Em notações como o Big-$\Theta$,
poderemos delimitar assintoticamente o crescimento do tempo de execução
dentro dos fatores constantes superiores e inferiores

Considere o seguinte exemplo:

*"O tempo de execução no **pior caso** da busca binária é $\Theta(lg n)$, estaria incorreto dizer que a busca binária executa em um tempo $\Theta(lg n)$ **todos** os casos. E se encontrarmos o valor desejado na primeira tentativa? Então o tempo que foi executado seria na verdade equivalente a $\Theta(1)$. O tempo de execução binária **nunca** será pior do que $\Theta(lg n)$, mas em algumas vezes poderá ser melhor"*

Portanto podemos dizer que o Big-$\Theta$ vem a ser uma forma
conveniente de notação assintótica para dizer que

### Diferença de Notações

É preciso relembrar a diferença de notações entre: Big-O e Big-$\Theta$

O Big-$\Theta$ é responsável por limitar o tempo de execução
**inferior** e **superior**, enquanto o Big-O apenas o superior. Se
dissermos que o tempo de execução é $\Theta(f(n))$ em uma caso
particular, ele também é $O(f(n))$, porém a regra inversa não é
necessariamente verdade, pois podemos dizer que, por exemplo, uma busca
binária sempre executa em um tempo $O(lg n)$ mas não que ela sempre
executa em $\Theta(lg n)$

Exercícios
----------

### Exércicio 1.1 

``` {.Scheme language="Scheme"}
10 = 10
(+ 5 3 4) = 12
(- 9 1) = 8
(/ 6 2) = 3
(+ (* 2 4) (- 4 6)) = 6
(define a 3)
(define b (+ a 1)) | b = 4
(+ a b (* a b)) = 19
(= a b) = false
(if (and (> b a) (< b (* a b))) | valor final = b
    b
    a)
(cond ((= a 4) 6)
      ((= b 4) (+ 6 7 a)) | valor final = 16
      (else 25))
(+ 2 (if (> b a) b a)) = 9
(* (cond ((> a b) a)
         ((< a b) b)
         (else -1))
   (+ a 1)) | valor final = 16
```

### Exercício 1.2 

``` {.Scheme language="Scheme"}
(define a (+ 5 4 (- 2 (- 3 (+ 6 (/ 4 5))))))

(define b (* 3 (- 6 2)(- 2 7)))

(define c (/ a b))
```

### Exercício 1.3

``` {.Scheme language="Scheme"}
(define numbers (list 5 2 6 1))

(define b1 (last (sort numbers <)))

(define b2 (second (sort numbers >)))

(define (sum-square b1 b2)
  (+ (* b1 b1) (* b2 b2)))
```

### Exercício 1.8 

``` {.Scheme language="Scheme"}
;; https://codology.net/post/sicp-solution-exercise-1-8/

(define (cube x) (* x x x))

(define (good-enough? previous-guess guess)
  (< (abs (/ (- guess previous-guess) guess)) 0.0000001))

(define (cube-root-iter guess x)
  (if (good-enough? (improve guess x) guess)
      guess
      (cube-root-iter (improve guess x) x)))

(define (improve guess x)
  (/ (+ (/ x (* guess guess)) (* 2 guess)) 3))

(define (cube-root x)
  (cube-root-iter 1.0 x))
```

### Exércicio 1.11 

``` {.Scheme language="Scheme"}
(define (func n)
  (cond ((< n 3) n)
        ((= n 3) (+ (func (- n 1)) (* 2 (func(- n 2))) (* 3 (func(- n 3)))))
        ((> n 3) (+ (func (- n 1)) (* 2 (func(- n 2))) (* 3 (func(- n 3)))))
        (else -1)))


(define (func2 n) 
  (if (< n 3)
      n
      (func-iter 2 1 0 2 n)))

(define (func-iter a b c nth n)
  (if (= n nth)
         a
         (func-iter (+ a (* 2 b ) (* 3 c)) a b (+ 1 nth) n)))
         
;;Iterative: https://codology.net/post/sicp-solution-exercise-1-11
```

.

### Exércicio 1.12

``` {.Scheme language="Scheme"}
#lang racket

(define (triang-pascal col lin)
  (cond ((= col 1) 1)
        ((= col lin) 1)
        ((= lin 1) 1)
        (else (+ (triang-pascal (- col 1) (- lin 1)) (triang-pascal (- col 1) lin)))))
```
