//Pilha dinamica.h

typedef struct aluno Aluno;
typedef struct elemento* Pilha;


//Protótipos/////////////////////

Pilha* cria();
void libera(Pilha *pi);
int tamanho(Pilha* pi);
int cheia(Pilha* pi);
int vazia(Pilha* pi);
int insere(Pilha* pi , struct aluno al);
int remover(Pilha* pi);
int consulta(Pilha* pi, struct aluno *al);
