typedef struct lista Lista;
typedef struct listano ListaNo;

Lista* cria();
void insere_ordenada(Lista* li, int dado);
void insere_inicio(Lista* li, int dado);
void imprime(Lista* li);
int pertence(Lista* li, int dado);
void libera(Lista* li);
void retirar(Lista* li,int dado);
int tamanho(Lista* li);
int retorna_ultimo(Lista* li);
void concatenarListas(Lista* li, Lista* l2);
Lista* particiona(Lista* li,int dado);

