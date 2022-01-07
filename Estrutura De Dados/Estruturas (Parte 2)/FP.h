#define MAX 100

typedef struct fila_prioridade FilaPrio;

FilaPrio* cria();
void libera(FilaPrio* fp);
int consulta(FilaPrio* fp, char* nome);
int insere(FilaPrio* fp, char* nome, int prio);
int remove(FilaPrio* fp);
int tamanho(FilaPrio* fp);
int cheia(FilaPrio* fp);
int vazia(FilaPrio* fp);