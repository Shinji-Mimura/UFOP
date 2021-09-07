#include "fitas.h"

//Inicializa Fitas de Entrada e Saida
void inicializaFitas(Fita *fitasE, Fita *fitasS)
{
    for (int i = 0; i < FITAS; i++)
    {
        fitasE[i].arquivo = NULL;
        fitasE[i].qtdBlocos = 0;
        fitasE[i].numReg = NULL;
        fitasS[i].arquivo = NULL;
        fitasS[i].qtdBlocos = 0;
        fitasS[i].numReg = NULL;
    }
}

//Obtem número de fitas disponíveis
int getFitasDisponiveis(Fita *fitas)
{
    int numFitas = 0;

    for (int i = 0; i < FITAS; i++)
    {
        if (fitas[i].qtdBlocos != 0)
        {
            numFitas++;
        }
        else
        {
            break;
        }
    }

    return numFitas;
}

int isContinua(int *count, int numFitas)
{
    int continua = 0;

    for (int i = 0; i < numFitas; i++)
    {
        if (count[i] < 0)
        {
            continua++;
        }
    }

    if (continua == numFitas)
    {
        return 0;
    }

    else
    {
        return 1;
    }
}

//Verifica se todos os valores dentro da heap estão marcados
bool isTudoMarcado(Heap *vetor, int valordeMarcacao, int reg)
{
    for (int i = 0; i < REG - reg; i++)
    {
        if (vetor[i].marcado <= valordeMarcacao / 2)
        {
            return false;
        }
    }

    return true;
}

//Desmarca todos os valores dentro da heap
void desmarcaTudo(Heap *vetor, int valordeMarcacao, int reg)
{
    for (int i = 0; i < REG - reg; i++)
    {
        vetor[i].marcado -= valordeMarcacao;
    }
}