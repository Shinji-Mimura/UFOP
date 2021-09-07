#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <signal.h>

pthread_t newthread_increment;
pthread_t newthread_decrement;
pthread_t newthread_saldo;

int saldo = 0;
char op;

void *printa_saldo(void *arg)
{
    do
    {
        if (op == 115)
        {
            printf("Saldo Thread ID => %ld\n", syscall(__NR_gettid));
            printf("Saldo: %d UD\n", saldo);
            op = 'x';
        } else if(op == 113) {
            pthread_exit(0);
        }
    } while(1);
}

void *increment(void *arg)
{

    do
    {
        if (op == 43)
        {
            printf("Incremento Thread ID => %ld\n", syscall(__NR_gettid));
            saldo += 100;
            op = 'x';
        } else if(op == 113) {
            pthread_exit(0);
        }
    } while(1);

        
}

void *decrement(void *arg)
{
    do
    {
        if (op == 45)
        {
            printf("Decremento Thread ID => %ld\n", syscall(__NR_gettid));
            saldo -= 50;
            op = 'x';
        } else if(op == 113) {
            pthread_exit(0);
        }
    } while(1);
}

int main(int argc, char const *argv[])
{

    pthread_create(&newthread_increment, NULL, increment, NULL);
    pthread_create(&newthread_decrement, NULL, decrement, NULL);
    pthread_create(&newthread_saldo, NULL, printa_saldo, NULL);

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
        op = getchar();
        getchar();
        

        if (op == 113)
        {
            printf("Finalizando Threads...\n");
            pthread_kill(newthread_increment, 0);
            pthread_kill(newthread_decrement, 0);
            pthread_kill(newthread_saldo, 0);
            printf("Finalizado!\n");
            return 0;
        }
 

    } while (op != 113);
}