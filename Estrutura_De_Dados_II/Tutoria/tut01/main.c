#include <stdlib.h>
#include <stdio.h>

#define ITENSPAGINA 8
#define MAXTABELA 1000

typedef struct
{
    int chave;
    long int preco;
    char titulo[10];
} tipoItem;

tipoItem item;

typedef struct
{
    int posicao;
    int chave;
} tipoIndice;

void text_to_bin(FILE *text, FILE *bin)
{

    printf("[!] Realizando Conversão TEXTO => BINÁRIO\n");

    while (fscanf(text, "%d %ld                   %[A-Z a-z]\n", &item.chave, &item.preco, item.titulo) != EOF)
    {
        //printf("%d %ld %s\n", item.chave, item.preco, item.titulo);
        fwrite(&item, sizeof(item), 1, bin);
    }

    printf("[+] Conversão finalizada\n");
}

int seq_search(tipoIndice tab[], int tam, tipoItem *item, FILE *arq)
{
    tipoItem pagina[ITENSPAGINA];
    int i = 0, quant_itens;
    long desloc;

    // procura na pagina a localização do item

    while (i < tam && tab[i].chave <= item->chave)
    {
        i++;
    }

    if (i == 0)
    {
        return 0;
    }

    else
    {
        if(i < tam){
            quant_itens = ITENSPAGINA;
        }

        else{
            fseek(arq, 0, SEEK_END);
            quant_itens = (ftell(arq)/sizeof(tipoItem)) % ITENSPAGINA;
        }

        desloc = (tab[i-1].posicao-1)*ITENSPAGINA*sizeof(tipoItem);
        fseek(arq, desloc, SEEK_SET);
        fread(&pagina, sizeof(tipoItem), quant_itens, arq);

        for(i = 0; i < quant_itens; i++){
            if(pagina[i].chave == item->chave){
                *item = pagina[i];
                return 1;
            }
        }

        return 0;

    }
}

int main(int argc, char const *argv[])
{

    FILE *arq;

    if ((arq = fopen("arqSequencial.txt", "r")) == NULL)
    {
        printf("Erro! O arquivo não pode ser aberto\n");
        exit(0);
    }

    // Conversão TEXTO -> Binário /////////

    FILE *arq2;
    arq2 = fopen("arqSequencialBin.bin", "wb");
    text_to_bin(arq, arq2);

    fclose(arq);
    fclose(arq2);

    //Pesquisa /////////

    tipoIndice tabela[MAXTABELA];
    tipoItem x;
    int pos, cont;

    if ((arq = fopen("arqSequencialBin.bin", "rb")) == NULL)
    {
        printf("Erro! O arquivo não pode ser aberto\n");
        exit(0);
    }

    // Geração de tabela de índice das páginas

    cont = 0;
    pos = 0;

    while (fread(&x, sizeof(x), 1, arq) == 1)
    {
        cont++;
        if (cont % ITENSPAGINA == 1)
        {
            tabela[pos].chave = x.chave;
            tabela[pos].posicao = pos + 1;
            pos++;
        }
    }

    fflush(stdout);
    printf("Digite o código desejado: ");
    scanf("%d", &x.chave);

    if(seq_search(tabela, pos, &x, arq)){
        printf("[+] Código Existente! Chave => %d Preço => %ld\n", x.chave, x.preco);
    }

    else{
        printf("[x] Código não encontrado!\n");
    }

    fclose(arq);

    return 0;
}
