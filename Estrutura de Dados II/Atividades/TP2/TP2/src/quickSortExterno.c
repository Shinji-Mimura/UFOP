#include "quickSortExterno.h"


void QuickSortExterno(FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, int Esq, int Dir, Estatisticas *est)
{
    int i, j;
    //Área Simples, composta de só um vetor de tamanho TAMAREA
    Aluno *Area = (Aluno*) malloc (TAMAREA * sizeof (Aluno));
    if (Dir - Esq < 1)
        return;
    FAVazia(Area);
    Particao(ArqLi, ArqEi, ArqLEs, Area, Esq, Dir, &i, &j, est);

    fflush(*ArqLi);
    fflush(*ArqEi);
    fflush(*ArqLEs);

    if (i - Esq < Dir - j){
        QuickSortExterno(ArqLi, ArqEi, ArqLEs, Esq, i, est);
        QuickSortExterno(ArqLi, ArqEi, ArqLEs, j, Dir, est);
    }else{
        QuickSortExterno(ArqLi, ArqEi, ArqLEs, j, Dir, est);
        QuickSortExterno(ArqLi, ArqEi, ArqLEs, Esq, i, est);
    }

    free (Area);
}

void FAVazia(Aluno *Area)
{
    //Preenchendo a área com lixo e -1, para verificações futuras
    for (int i = 0; i < TAMAREA; i++)
    {
        Area[i].inscricao = -1;
        Area[i].nota = -1.0;
        strcpy(Area[i].estado, "lixo");
        strcpy(Area[i].cidade, "lixo");
        strcpy(Area[i].curso, "lixo");
    }
}

int ObterNumCelOcupadas(Aluno *Area, Estatisticas *est)
{
    int cont = 0;
    incComparacao(est);
    while (Area[cont].inscricao != -1 && cont < TAMAREA)
    {
        //Para saber quantas células estã ocupadas, basta saber quantas não tem -1 no lugar da inscrição
        incComparacao(est);
        cont++;
    }

    return cont;
}

//Funções básicas do QuickSort Externo

void LeSup(FILE **ArqLEs, Aluno *UltLido, int *Ls, short *OndeLer, Estatisticas *est)
{
    fseek(*ArqLEs, (*Ls - 1) * sizeof(Aluno), SEEK_SET);
    incTransferenciaLeitura(est);
    fread(UltLido, sizeof(Aluno), 1, *ArqLEs);
    (*Ls)--;
    *OndeLer = FALSE;
}

void LeInf(FILE **ArqLi, Aluno *UltLido, int *Li, short *OndeLer, Estatisticas *est)
{
    incTransferenciaLeitura(est);
    fread(UltLido, sizeof(Aluno), 1, *ArqLi);
    (*Li)++;
    *OndeLer = TRUE;
}

void EscreveMax(FILE **ArqLEs, Aluno R, int *Es, Estatisticas *est)
{
    fseek(*ArqLEs, (*Es - 1) * sizeof(Aluno), SEEK_SET);
    incTransferenciaEscrita(est);
    fwrite(&R, sizeof(Aluno), 1, *ArqLEs);
    (*Es)--;
}

void EscreveMin(FILE **ArqEi, Aluno R, int *Ei, Estatisticas *est)
{
    incTransferenciaEscrita(est);
    fwrite(&R, sizeof(Aluno), 1, *ArqEi);
    (*Ei)++;
}

void RetiraMax(Aluno *Area, Aluno *R, int *NRArea, Estatisticas *est)
{
    RetiraUltimo(Area, R, est);
    *NRArea = ObterNumCelOcupadas(Area, est);
}

void RetiraMin(Aluno *Area, Aluno *R, int *NRArea, Estatisticas *est)
{
    RetiraPrimeiro(Area, R, est);
    *NRArea = ObterNumCelOcupadas(Area, est);
}

void RetiraUltimo(Aluno *Area, Aluno *R, Estatisticas *est)
{
    int cont = 0;
    incComparacao(est);
    while (Area[cont].inscricao != -1 && cont < TAMAREA)
    {
        //esse while procura o ultimo aluno dentro da Área
        incComparacao(est);
        cont++;
    }

    cont--;
    *R = Area[cont];
    //guardo em R para retorno por referencia

    // completo com lixo e -1 essa posição retirada
    Area[cont].inscricao = -1;
    Area[cont].nota = -1.0;
    strcpy(Area[cont].estado, "lixo");
    strcpy(Area[cont].cidade, "lixo");
    strcpy(Area[cont].curso, "lixo");
}

//Retira o primeiro Aluno presente na Área
void RetiraPrimeiro(Aluno *Area, Aluno *R, Estatisticas *est)
{
    int i = 0, j = 1;
    //faço o retorno por referencia
    *R = Area[0];
    incComparacao(est);
    while (Area[j].inscricao != -1 && i < TAMAREA - 1)
    {
        //reorganizo a área, jogando tudo pras primeiras posições
        incComparacao(est);
        Area[i] = Area[j];
        i++;
        j++;
    }

    //completo com lixo no ultimo elemento
    Area[i].inscricao = -1;
    Area[i].nota = -1.0;
    strcpy(Area[i].estado, "lixo");
    strcpy(Area[i].cidade, "lixo");
    strcpy(Area[i].curso, "lixo");
}

void InsereItem(Aluno UltLido, Aluno *Area, Estatisticas *est)
{
    int i = 0; //percorre
    int j = 8; //antepenultimo item da area
    int k = 9; //penultimo item da área
    incComparacao(est);
    incComparacao(est);
    while (Area[i].nota < UltLido.nota && Area[i].inscricao != -1 && i < TAMAREA)
    {
        //percorro a área em busca do local adequado para inserção do item
        incComparacao(est);
        incComparacao(est);
        i++;
    }

    while (j >= i)
    {
        //reorganizo a área de acordo com o índice no vetor
        Area[k] = Area[j];
        j--;
        k--;
    }
    //faço a inserção no indice
    Area[i] = UltLido;
}

void InserirArea(Aluno *Area, Aluno *UltLido, int *NRArea, Estatisticas *est)
{
    //Insere UltLido de forma ordenada na Area
    InsereItem(*UltLido, Area, est);
    *NRArea = ObterNumCelOcupadas(Area, est);
}

//Funçção de Partição do QuickSort Externo
void Particao(FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, Aluno *Area, int Esq, int Dir, int *i, int *j, Estatisticas *est)
{
    int Ls = Dir;
    int Es = Dir;
    int Li = Esq;
    int Ei = Esq;
    int NRArea = 0;
    double Linf = INT_MIN;
    double Lsup = INT_MAX;

    short OndeLer = TRUE;

    Aluno R;

    fseek(*ArqLi, (Li - 1) * sizeof(Aluno), SEEK_SET);
    fseek(*ArqEi, (Ei - 1) * sizeof(Aluno), SEEK_SET);

    *i = Esq - 1;
    *j = Dir + 1;

    while (Ls >= Li)
    {
        Aluno UltLido;

        if (NRArea < TAMAREA - 1)
        {

            if (OndeLer)
            {
                LeSup(ArqLEs, &UltLido, &Ls, &OndeLer, est);
            }
            else
            {
                LeInf(ArqLi, &UltLido, &Li, &OndeLer, est);
            }

            InserirArea(Area, &UltLido, &NRArea, est);

            continue;
        }

        if (Ls == Es)
        {
            LeSup(ArqLEs, &UltLido, &Ls, &OndeLer, est);
        }
        else if (Li == Ei)
        {
            LeInf(ArqLi, &UltLido, &Li, &OndeLer, est);
        }
        else if (OndeLer)
        {
            LeSup(ArqLEs, &UltLido, &Ls, &OndeLer, est);
        }
        else
        {
            LeInf(ArqLi, &UltLido, &Li, &OndeLer, est);
        }

        incComparacao(est);
        if (UltLido.nota > Lsup)
        {
            *j = Es;
            EscreveMax(ArqLEs, UltLido, &Es, est);
            continue;
        }

        incComparacao(est);
        if (UltLido.nota < Linf)
        {
            *i = Ei;
            EscreveMin(ArqEi, UltLido, &Ei, est);
            continue;
        }

        InserirArea(Area, &UltLido, &NRArea, est);

        if (Ei - Esq < Dir - Es)
        {
            RetiraMin(Area, &R, &NRArea, est);
            EscreveMin(ArqEi, R, &Ei, est);
            Linf = R.nota;
        }
        else
        {
            RetiraMax(Area, &R, &NRArea, est);
            EscreveMax(ArqLEs, R, &Es, est);
            Lsup = R.nota;
        }
    }

    while (Ei <= Es)
    {
        RetiraMin(Area, &R, &NRArea, est);
        EscreveMin(ArqEi, R, &Ei, est);
    }
}

void imprimirArea(Aluno *Area)
{
    printf("===== Área =====\n");
    for (int i = 0; i < TAMAREA; i++)
    {
        imprimeAluno(Area[i]);
    }
    printf("\n");
}