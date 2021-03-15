struct aluno{
    int mat;
    char nome[30];
    float n1,n2,n3;
};

typedef struct fila Fila;
Fila* criaFila();
void libera_fila(Fila* fi);
void insere(Fila* fi,int x);