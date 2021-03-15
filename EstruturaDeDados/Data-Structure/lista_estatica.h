// lista estática .h

#define MAX 100

typedef struct aluno Aluno;
typedef struct lista Lista;

//Protótipos///////////////

Lista* cria();
void libera(Lista* li);
int insere_final(Lista* li, struct aluno al);
int insere_inicio(Lista* li, struct aluno al);
int insere_ordenada(Lista* li, struct aluno al);
Lista* particiona(Lista* li, int matr);
void concatena(Lista* li,Lista* li2);