#include "TabelaHash.hpp"

//O tamanho ideal é algo que seja primo ou que não seja potência de dois
// Números primos reduzem colisões
// Potência de dois aumentam problemas de colisão

//Similar a Lista Sequencial Estática

struct aluno
{
    int mat;
    char nome[30];
    float n1,n2,n3;
};

struct hash
{
    int qtd, tamanho_tabela;
    struct aluno **itens;

};


//Funções////////////////

Hash* cria(int tam_tabela)
{
    Hash* aux = (Hash*) malloc(sizeof(Hash));

    if (aux != NULL)
    {
        int i;
        aux->tamanho_tabela = tam_tabela;
        aux->itens = (struct aluno**) malloc(tam_tabela*sizeof(struct aluno*));
        aux->qtd = 0;
        if (aux->itens == NULL)
        {
            free(aux);
            return NULL;
        }

        for (i = 0; i < aux->tamanho_tabela ; i++)
        {
            aux->itens[i] = NULL;
        }
    }

    return aux;

}
void libera(Hash* ha)
{
    if(ha != NULL)
    {
        for (int i = 0; i < ha->tamanho_tabela; i++)
        {
            if (ha->itens[i] != NULL)
            {
                free(ha->itens[i]);
            }
        }

    free(ha->itens);
    free(ha);

    }

}

int chaveDivisao(int chave, int tam_tabela)
{
    return(chave & 0x7FFFFFFF) % tam_tabela;
}

int chaveMultiplicacao(int chave, int tam_tabela)
{
    float A = 0.6180339887;
    float val = chave * A;
    val = val - (int) val;
    return (int) (tam_tabela * val);
}

int chaveDobra(int chave, int tam_tabela)
{
    int num_bits = 10;
    int parte1 = chave >> num_bits;
    int parte2 = chave & (tam_tabela-1);
    return (parte1 ^ parte2);
}

int valorString(char *str)
{
    int valor = 7;
    int tam = strlen(str);
    for (int i = 0; i < tam; i++)
    {
        valor = 31 * valor + (int) str[i];
    }

    return valor;

}
int insere(Hash* ha, struct aluno al)
{
    if (ha == NULL || ha->qtd == ha->tamanho_tabela)
    {
        return 0;
    }

    int chave = al.mat;
    int pos = chaveDivisao(chave,ha->tamanho_tabela);
    Aluno* novo;
    novo = new Aluno;
    *novo = al;
    ha->itens[pos] = novo;
    ha->qtd++;
    return 1;

}
int busca(Hash* ha, int mat, struct aluno al)
{
    if (ha == NULL)
    {
        return 0;
    }

    int pos = chaveDivisao(mat,ha->tamanho_tabela);
    if (ha->itens[pos] == NULL)
    {
        return 0;
    }

    al = *(ha->itens[pos]);
    return 1;



}

int sondagem_linear(int pos, int i, int tam_tabela)
{
    return ((pos + i) & 0x7FFFFFFF) % tam_tabela;
}

int sondagem_quadratica(int pos, int i, int tam_tabela)
{
    pos = pos + 2*i + 5*i*i;
    return ((pos + i) & 0x7FFFFFFF) % tam_tabela;
}

int duploHash(int H1, int chave, int i, int tam_tabela)
{
    int H2 = chaveDivisao(chave,tam_tabela-1) + 1;
    return ((H1 + i*H2) & 0x7FFFFFFF) % tam_tabela;
}

int insere_endAberto(Hash* ha, struct aluno al)
{
    if (ha == NULL || ha->qtd == ha->tamanho_tabela)
    {
        return 0;
    }

    int chave = al.mat;
    int i,pos,newpos;
    pos = chaveDivisao(chave,ha->tamanho_tabela); //Posição inicial da chave na tabela

    for ( i = 0; i < ha->tamanho_tabela; i++)
    {
        newpos = sondagem_linear(pos,i,ha->tamanho_tabela);
        if (ha->itens[newpos] == NULL)
        {
            struct aluno* novo = (struct aluno*) malloc(sizeof(Aluno));
            *novo = al;
            ha->itens[newpos] = novo;
            ha->qtd++;
            return 1;
        }

    }

    return 0;
}
int busca_endAberto(Hash* ha, int mat, struct aluno* al)
{

    if (ha == NULL)
    {
        return 0;
    }

    int i, pos, newpos;
    pos = chaveDivisao(mat,ha->tamanho_tabela);
    for ( i = 0; i < ha->tamanho_tabela; i++)
    {
        newpos = sondagem_linear(pos,i,ha->tamanho_tabela);
        if (ha->itens[newpos] == NULL)
        {
            return 0;
        }

        if (ha->itens[newpos]->mat == mat)
        {
            *al = *(ha->itens[newpos]);
            return 1;
        }

    }

    return 0;

}

void B()
{
    Hash* h;
    h = cria(1400); // Cria Tabela Hash

    Aluno al1; // Perfil do aluno 1
    al1.mat = 1234;
    al1.n1 = 10;
    al1.n2 = 8;
    al1.n3 = 9;
    strcpy(al1.nome,"Amanda");

    Aluno al2; // Perfil do aluno 2
    al2.mat = 1235;
    al2.n1 = 9;
    al2.n2 = 8;
    al2.n3 = 9;
    strcpy(al2.nome,"Dayane");

    Aluno al3; // Perfil do aluno 3
    al3.mat = 1236;
    al3.n1 = 7;
    al3.n2 = 6;
    al3.n3 = 10;
    strcpy(al3.nome,"Tulio");

    insere_endAberto(h,al1); // Insere na tabela utilizando endereçamento aberto para evitar colisões
    insere_endAberto(h,al2); // Insere na tabela utilizando endereçamento aberto para evitar colisões
    insere_endAberto(h,al3); // Insere na tabela utilizando endereçamento aberto para evitar colisões

    Aluno *aux = new Aluno;

    int x = busca_endAberto(h,1234,aux); // Busca  aluno 1 utilizando endereçamento aberto

    if (x == 1)
    {
        printf("Aluno encontrado !\n");
        printf("Matricula = %d Nota 1 = %f Nota 2 = %f Nota 3 = %f Nome = %s",aux->mat,aux->n1,aux->n2,aux->n3,aux->nome);
        printf("\n");
    }


    else
    {
        printf("Aluno não encontrado !\n");
    }

    libera(h); // Libera memória

}
