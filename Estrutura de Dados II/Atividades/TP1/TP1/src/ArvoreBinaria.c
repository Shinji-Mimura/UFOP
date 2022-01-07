#include "ArvoreBinaria.h"

/*
* Implementação da Simulação da Árvore Binária de Pesquisa sem recursão,
* usando iteradores: um para caminhar no arquivo de entrada, e outro para caminhar
* no arquivo que será a minha árvore
*/
void criaArvoreBinaria(FILE *in, FILE *out, Estatisticas *a)
{
    rewind(in);
    Registro reg;
    Node filho;
    Node nodeAux;

    int cont = 0;
    int posFilho = 0;
    int flag = 1;

    incTransferencia(a);
    //while que lê o arquivo de entrada
    while (fread(&reg, sizeof(Registro), 1, in) == 1)
    {
        incTransferencia(a);
        flag = 1; //coloco o flag em 1 para entrar no while abaixo
        //faço a gravação no arquivo de saída
        filho.dir = -1;
        filho.esq = -1;
        filho.reg = reg;
        filho.pos = cont;

        incTransferencia(a);
        fwrite(&filho, sizeof(Node), 1, out);

        cont++;

        if (cont != 1)
        {                 //esse if é pra certificar de que não leia novamente o "nó raiz"
            rewind(out);  //certificando que sempre estarei no inicio do arquivo sempre que estiver nesse primeiro while
            posFilho = 0; //essa variavel é sempre limpa nas iterações
            incTransferencia(a);
            //esse while é pra ler o arquivo de saída
            while (fread(&nodeAux, sizeof(Node), 1, out) == 1 && flag == 1)
            {
                incTransferencia(a);
                incComparacao(a);
                //assim como numa árvore binaria comum, faço a leitura do nó pai e comparo com o nó onde eu quero colocar...
                if (reg.chave < nodeAux.reg.chave)
                    if (nodeAux.esq == -1)
                    { //esse -1 serve como meu NULL, então se eu encontrar um nó vazio, será aqui que eu vou escrever
                        nodeAux.esq = cont - 1;
                        fseek(out, posFilho * sizeof(Node), 0);
                        incTransferencia(a);
                        fwrite(&nodeAux, sizeof(Node), 1, out);
                        flag = 0; //graças a essa variavel, se eu encontro um nó vazio, seto ela como 0, e saio desse while
                    }
                    else
                    { //senão, continuo percorrendo o arquivo até encontrar
                        fseek(out, (nodeAux.esq) * sizeof(Node), 0);
                        posFilho = nodeAux.esq;
                    }
                else
                {
                    if (nodeAux.dir == -1)
                    {
                        nodeAux.dir = cont - 1;
                        fseek(out, posFilho * sizeof(Node), 0);
                        incTransferencia(a);
                        fwrite(&nodeAux, sizeof(Node), 1, out);
                        flag = 0;
                    }
                    else
                    {
                        fseek(out, (nodeAux.dir) * sizeof(Node), 0);
                        posFilho = nodeAux.dir;
                    }
                }
            }
        }
        fseek(out, 0, SEEK_END);
    }
}

int pesquisaArvoreBinaria(FILE *arvore, Node *nodeAux, Registro pesquisado, Estatisticas *est)
{
    fread(nodeAux, sizeof(Node), 1, arvore);

    if (nodeAux->reg.chave == pesquisado.chave)
    {
        return 1;
        incComparacao(est);
    }
    else if (pesquisado.chave > nodeAux->reg.chave && nodeAux->dir != -1)
    {
        fseek(arvore, nodeAux->dir * sizeof(Node), SEEK_SET);
        incComparacao(est);
        return (pesquisaArvoreBinaria(arvore, nodeAux, pesquisado, est));
    }
    else if (pesquisado.chave < nodeAux->reg.chave && nodeAux->esq != -1)
    {
        fseek(arvore, nodeAux->esq * sizeof(Node), SEEK_SET);
        incComparacao(est);
        return (pesquisaArvoreBinaria(arvore, nodeAux, pesquisado, est));
    }

    return 0;
}