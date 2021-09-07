#include "intercala.h"

#define RESULTANTE (fitaResultante - 1) % FITAS

// Função que inicializa o metodo de ordenação 1
void intercala2F(FILE *arq, int tamanho, Estatisticas *est)
{
    Fita fitasE[FITAS];
    Fita fitasS[FITAS];
    Aluno registros[REG];
    inicializaFitas(fitasE, fitasS);

    //Função que gera os blocos nas fitas
    criaBlocosIntercalacao(arq, fitasE, tamanho, est);

    //A variável trocaFitas determina quais fitas serão usadas
    //11 a 20 (0)  &   1 a 10 (1)
    int trocaFitas = 1, continua = 1;
    while (continua)
    {
        if (trocaFitas == 1)
        {
            continua = intercala(fitasE, fitasS, registros, trocaFitas, est);
            trocaFitas = !trocaFitas;
        }

        else
        {
            continua = intercala(fitasS, fitasE, registros, trocaFitas, est);
            trocaFitas = !trocaFitas;
        }
    }
}

// Gera as fitas de entrada
void criaBlocosIntercalacao(FILE *arq, Fita *fitas, int tamanho, Estatisticas *est)
{
    // valordeMarcacao pode ser qualquer valor alto para marcação do heap
    int count = 0, countReg = 0, reg = 0, valordeMarcacao = 2000;
    char nomeArq[20];
    Heap regHeap[REG];

    // Lê os registros para os blocos
    for (int i = 0; i < REG; i++)
    {
        incTransferenciaLeitura(est);
        fread(&regHeap[i].registro, sizeof(Aluno), 1, arq);
        regHeap[i].marcado = regHeap[i].registro.nota;
    }

    while (tamanho != 0)
    {
        // Realiza o heapsort com os registros
        heapSort(regHeap, REG - reg, est);

        // Criando as fitas
        if (count < FITAS && fitas[count % FITAS].arquivo == NULL)
        {
            sprintf(nomeArq, "fita-%d.bin", count + 1);
            fitas[count % FITAS].arquivo = fopen(nomeArq, "w+b");
        }

        else
        {
            sprintf(nomeArq, "fita-%d.bin", (count % FITAS) + 1);
            fseek(fitas[count % FITAS].arquivo, 0, SEEK_END);
        }

        // Verifica se o vetor esta todo marcado
        if (isTudoMarcado(regHeap, valordeMarcacao, reg))
        {
            desmarcaTudo(regHeap, valordeMarcacao, reg);
            fitas[count % FITAS].qtdBlocos++;

            // Faz a criação de um vetor para cada bloco presente dentro das fitas
            int *aux = malloc((count / FITAS + 1) * sizeof(int));

            // Garante que a variavel aux tenha o tamanho correto de blocos presente em cada fita
            // Atribui a quantidade de registros para cada posição da variavel aux e aponta numReg para aux
            if ((count / FITAS + 1) == 1)
            {
                aux[0] = countReg;
                fitas[count % FITAS].numReg = aux;
            }

            else
            {
                // Pega todos os registros ja contidos dentro da fita adicionando a quantidade de registros do novo bloco
                for (int i = 0; i < count / FITAS; i++)
                {
                    aux[i] = fitas[count % FITAS].numReg[i];
                }

                aux[count / FITAS] = countReg;
                fitas[count % FITAS].numReg = aux;
            }

            count++;
            countReg = 0;
        }

        else
        {
            // Pega o menor registro do vetor regHeap
            Heap old = regHeap[0];

            // Escreve o valor na fita
            incTransferenciaEscrita(est);
            fwrite(&old.registro, sizeof(Aluno), 1, fitas[count % FITAS].arquivo);
            countReg++;

            // Garantindo que não haja leitura desnecessária
            if (tamanho - REG > 0)
            {
                incTransferenciaLeitura(est);
                fread(&regHeap[0].registro, sizeof(Aluno), 1, arq);

                incComparacao(est);
                // A marcação utilizada é aumentando o valor inicial da nota em um valor arbitrário
                if (regHeap[0].registro.nota < old.registro.nota)
                {
                    regHeap[0].marcado = regHeap[0].registro.nota + valordeMarcacao;
                }

                else
                {
                    regHeap[0].marcado = regHeap[0].registro.nota;
                }
            }

            // Manipula os registros restantes que estão dentro do vetor regHeap
            else
            {
                // Pega o ultimo registro e joga ele para a primeira posição
                old = regHeap[REG - reg - 1];
                regHeap[0] = old;
                reg++;
            }

            tamanho--;
        }
    }

    fitas[count % FITAS].qtdBlocos++;

    // Garante que a quantidade de registros restantes seja armazenada na fita

    // Faz a criação de um vetor para cada bloco presente dentro das fitas
    int *aux = malloc((count / FITAS + 1) * sizeof(int));

    // Garante que a variavel aux tenha o tamanho correto de blocos presente em cada fita
    // Atribui a quantidade de registros para cada posição da variavel aux e aponta numReg para aux
    if ((count / FITAS + 1) == 1)
    {
        aux[0] = countReg;
        fitas[count % FITAS].numReg = aux;
    }

    else
    {
        // Pega todos os registros ja contidos dentro da fita adicionando a quantidade de registros do novo bloco
        for (int i = 0; i < count / FITAS; i++)
        {
            aux[i] = fitas[count % FITAS].numReg[i];
        }

        // Insere na ultima posição
        aux[count / FITAS] = countReg;
        fitas[count % FITAS].numReg = aux;
    }
}

// Função principal de intercalação. retorna 0 caso a intercalação tenha terminado e 1 caso contrário
int intercala(Fita *fitasE, Fita *fitasS, Aluno *registro, int trocaFitas, Estatisticas *est)
{
    int numFitas = 0;
    char nomeArq[20];

    // A fita selecionada para ser a fita final da ordenação
    int fitaSelecionada;

    //A fita que será manipulada
    int fitaResultante;
    if (trocaFitas == 1)
    {
        fitaSelecionada = 1;
        fitaResultante = FITAS + 1;
    }
    else
    {
        fitaSelecionada = FITAS + 1;
        fitaResultante = 1;
    }
    int valordeMarcacao = 0;

    // Confere o numero de fitas válidas
    numFitas = getFitasDisponiveis(fitasE);

    // Com todos os blocos ordenados numa única fita, é encerrado o programa
    if (numFitas == 1)
    {
        sprintf(nomeArq, "fita-%d.bin", fitaSelecionada);

        // Fecha todos os arquivos
        for (int i = 0; i < FITAS; i++)
        {
            if (fitasE[i].arquivo != NULL)
            {
                fclose(fitasE[i].arquivo);
            }

            if (fitasS[i].arquivo != NULL)
            {
                fclose(fitasS[i].arquivo);
            }
        }

        rename(nomeArq, "temp.bin");
        for (int i = 0; i < FITAS * 2; i++)
        {
            sprintf(nomeArq, "fita-%d.bin", i + 1);
            remove(nomeArq);
        }

        return 0;
    }

    // Reinicia os ponteiros das fitas
    for (int i = 0; i < numFitas; i++)
    {
        fseek(fitasE[i].arquivo, 0, SEEK_SET);
    }

    //Início da intercalação //////////////////////////

    // Cria um vetor com o numero maximo de fitas que sera utilizado
    int *count = malloc(numFitas * sizeof(int));
    int posicao;

    // continua determina se a intercalação deve continuar
    int continua;
    int index = 0;
    int *aux;
    Aluno menor;

    while (numFitas != 0)
    {
        // Atribui ao contador o numero de registros disponível em cada arquivo
        for (int i = 0; i < numFitas; i++)
        {
            count[i] = fitasE[i].numReg[index];
        }

        // Faz a leitura do primeiro item de cada bloco
        for (int i = 0; i < numFitas; i++)
        {
            incTransferenciaLeitura(est);
            fread(&registro[i], sizeof(Aluno), 1, fitasE[i].arquivo);
            count[i]--;
        }

        continua = 1;
        sprintf(nomeArq, "fita-%d.bin", fitaResultante);
        // Cria a fita quando não existem fitas de saida
        if (fitasS[RESULTANTE].arquivo == NULL)
        {
            fitasS[RESULTANTE].arquivo = fopen(nomeArq, "w+b");
        }

        // Apenas continua
        else if (fitasS[RESULTANTE].arquivo != NULL && fitasS[RESULTANTE].qtdBlocos != 0)
        {
            continua = 1;
        }

        // Move o ponteiro para o inicio do arquivo quando as fitas de saida já se encontram criadas
        else
        {
            fseek(fitasS[RESULTANTE].arquivo, 0, SEEK_SET);
        }

        // Verifica se tem ou não blocos nas fitas
        if (valordeMarcacao / FITAS == 0)
        {
            // Faz a alocação do vetor aux
            aux = malloc((valordeMarcacao / FITAS + 1) * sizeof(int));
            // Caso não tenha blocos, o aux simplesmente recebe 0 e o numReg é apontado para ele
            aux[0] = 0;
            fitasS[RESULTANTE].numReg = aux;
        }

        else
        {
            aux = malloc((valordeMarcacao / FITAS + 1) * sizeof(int));
            for (int i = 0; i < valordeMarcacao / FITAS; i++)
            {
                aux[i] = fitasS[RESULTANTE].numReg[i];
            }

            // Caso tenha blocos na fita, o aux copia tudo o que está no numReg, atribui 0 para a ultima posição do aux e numReg é apontado para ele
            aux[valordeMarcacao / FITAS] = 0;
            fitasS[RESULTANTE].numReg = aux;
        }

        while (continua)
        {
            menor.nota = RAND_MAX;
            posicao = -1;

            // Procura qual é a menor nota presente no vetor registro, guardando ele e sua posição
            for (int i = 0; i < numFitas; i++)
            {
                incComparacao(est);
                if (registro[i].nota <= menor.nota && count[i] >= 0)
                {
                    menor = registro[i];
                    posicao = i;
                }
            }

            // Realiza a escrita do registro na fita de saida e le um novo registro da fita de entrada
            incTransferenciaEscrita(est);
            fwrite(&menor, sizeof(Aluno), 1, fitasS[RESULTANTE].arquivo);
            fitasS[RESULTANTE].numReg[valordeMarcacao / FITAS]++;

            // Lê apenas a quantidade de registros presente no bloco
            if (count[posicao] > 0)
            {
                incTransferenciaLeitura(est);
                fread(&registro[posicao], sizeof(Aluno), 1, fitasE[posicao].arquivo);
            }

            count[posicao]--;

            // Confere se os registros de todos os blocos foram lidos
            continua = isContinua(count, numFitas);
        }

        for (int i = 0; i < numFitas; i++)
        {
            fitasE[i].qtdBlocos--;
        }

        fitasS[RESULTANTE].qtdBlocos++;

        numFitas = getFitasDisponiveis(fitasE);
        fitaResultante++;
        index++;
        valordeMarcacao++;
    }

    free(count);

    return 1;
}
