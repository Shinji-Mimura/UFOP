#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define LEITURA 0
#define ESCRITA 1

int incrementar(int saldo)
{

    saldo += 100;
    return saldo;
}

int decrementar(int saldo)
{

    saldo -= 50;
    return saldo;
}

int main(int argc, char const *argv[])
{

    char opcao = 'x';

    int auxiliar = 0;
    int saldo_fd[2];
    pipe(saldo_fd);
    write(saldo_fd[ESCRITA], &auxiliar, sizeof(int));

    int op_fd[2];
    pipe(op_fd);

    pid_t pid_pai = getpid();
    pid_t filho1 = fork();


    fflush(stdin);

    pid_t filho2 = -1;

    if (getpid() == pid_pai)
    {
        filho2 = fork();

        if(filho2 < 0){
            exit(1);
        }

        if (filho2 == 0)
        {
            filho1 = -1;
        }
    }

    //printf(" PAI = %d\n FILHO 1 = %d\n FILHO 2 = %d\n", pid_pai, filho1, filho2);    


    if (getpid() == pid_pai)
    {
        int valor_aux;

        while (opcao != 'q')
        {
            do
            {
                printf("+------------------------------+\n");
                printf("Selecione Qual Opção Deseja:\n");
                printf("[+] Para acrescer 100 UD \n");
                printf("[-] Para decrescer 50 UD\n");
                printf("[s] Para visualizar saldo atual\n");
                printf("[q] Para sair\n");
                printf("+------------------------------+\n");
                printf("Opção: ");
                opcao = getchar();
                getchar();

            } while (opcao != 'q');

            if (opcao == 's')
            {

                read(saldo_fd[LEITURA], &valor_aux, sizeof(int));
                read(saldo_fd[ESCRITA], &valor_aux, sizeof(int));
                printf("Saldo => %d UD\n", valor_aux);
                printf("PID Saldo => %d\n", getpid());
            }

            else
            {
                write(op_fd[ESCRITA], &opcao, sizeof(char));
            }

            if (opcao == 'q')
            {
                printf("Encerrando Forks...\n");
                kill(filho1, SIGKILL);
                kill(filho2, SIGKILL);
                int pid_atual = getpid();
                kill(pid_atual, SIGKILL);
                printf("Finalizado!\n");
                exit(0);
            }
        }
    }


    else if (filho1 == 0)
    {
        char operador;
        int valor_aux;
        
        do
        {

            read(op_fd[LEITURA], &operador, sizeof(char));

            if (operador == '+')
            {
                printf("Acréscimo de 100 unidades\n");
                printf("PID Somador => %d\n", getpid());
                read(saldo_fd[LEITURA], &valor_aux, sizeof(int));
                valor_aux = incrementar(valor_aux);
                write(saldo_fd[ESCRITA], &valor_aux, sizeof(int));
            }

            else
            {
                write(op_fd[ESCRITA], &opcao, sizeof(char));
            }

        } while (operador == 'q');
    }

    else if (filho2 == 0)
    {
        char operador;
        int valor_aux;
        
        do
        {

            read(op_fd[LEITURA], &operador, sizeof(char));

            if (operador == '-')
            {
                printf("Decréscimo de 50 unidades\n");
                printf("PID Decréscimo => %d\n", getpid());
                read(saldo_fd[LEITURA], &valor_aux, sizeof(int));
                valor_aux = decrementar(valor_aux);
                write(saldo_fd[ESCRITA], &valor_aux, sizeof(int));
            }

            else
            {
                write(op_fd[ESCRITA], &opcao, sizeof(char));
            }

        } while (operador == 'q');
    }

    return 0;
}