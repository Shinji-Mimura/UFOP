Prelúdio
--------

Neste capítulo nos é apresentado a familia de linguagens `Lisp`,
concebida por McCarthy em 1960 e, que tem como proposta poder ter
funções matemáticas para montar sua estruturas de dados.

Lisp no começo não possuía tanta eficiência em computações numéricas por
conta de seu caráter experimental. Após anos de aperfeiçoamento, Lisp
foi ganhando espaço e hoje é bem popular em meios como a `shell` dos
sistemas operacionais, meios estes que não tem como preocupação central
o parâmetro de eficiência.

A família Lisp é ótima para o estudo de estrutura de dados e suas relações.

Elementos da Programação
------------------------

Linguagens podem servir de `frameworks` para organizar nossas ideias a
respeito de processos, toda linguagem poderosa tem três mecanismos que
permitem isto:

-   **Expressões Primitivas**

    Entidades mais simples que a linguagem procura se preocupar

-   **Meios de Combinação**

    Forma pela qual elementos compostos são construídos através de
    elementos mais simples

-   **Meios de Abstração**

    Formas pela qual elementos compostos são manipulados como unidades

Combinações
-----------

As combinações são feitas de forma recursiva, com operador mais a
esquerda e sempre executando as operações mais internas da expressão

Considere o seguinte trecho de código:

```
(* (+ 2 (* 4 6)) (+ 3 5 7))
```

A regra de avaliação será aplicada em quatro operações através da
técnica de recursão(A recursão é uma técnica poderosa para lidar com os objetos e
suas respectivas hierarquias). Tendo em vista isso, as operações podem
ser escritas na seguinte ordem:

1.  \* 4 6 = 24

    *Estas duas expressões estão no mesmo nível de hierarquia*

    2.  \+ 2 24 = 26

    3.  \+ 3 5 7 = 15

2.  \* 26 15 = 390

Modelo de Substituição
----------------------

No processo realizado pelo modelo de substituição, você substitui cada
parâmetro formal no corpo da expressão pelo valor do argumento
correspondente

Podemos ilustrar isto da seguinte forma, considere a expressão a seguir:

```
(define (sum-of-squares x y)  
     (+ (square x) (square y)))
     (define (square x) (* x x))
```

Chamaremos a função da seguinte forma: `(sum-of-squares 3 4)`

1.  Nós temos um parâmetro formal, `x`, que é chamado como argumento 3 e
    `y`, que é chamado como argumento 4

2.  Agora cada ocorrência de `x` e `y` no corpo da equação será
    substituído respectivamente por 3 e 4

3.  O corpo da equação então terá está aparência:
    `(+ (square 3) (square 4))`

4.  Usando a definição de `square`, isto se torna: `(+ (* 3 3) (* 4 4))`

5.  Aplicando a multiplicação em ambos, temos: `(+ 9 16)`

6.  Aplicamos a soma e no final teremos 25 como resultado

O objetivo da substituição é nos ajudar a pensar sobre a aplicação do
procedimento e não fornecer uma descrição precisa de como o intérprete
realmente funciona. Os intérpretes típicos não avaliam as aplicações do
procedimento manipulando o texto para substituir valores dos parâmetros
formais
