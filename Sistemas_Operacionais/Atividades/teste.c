#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#define READ_POS  0
#define WRITE_POS 1

void display(int saldo);

/**
 * Trabalho Prático II - Sistemas Operacionais - FORK
 * Aluno: Vinicius Gabriel Angelozzi Verona de Resende 
 * Matricula: 19.1.4005 
 * Professor: Dr. Carlos Frederico 
*/
int main(){

    display(0);
    
    // Captura do valor da tecla sem pressionar _enter_
    system("/bin/stty raw");

    int saldo_pipe[2];
    int key_pipe[2];
    int option = 0;

    // Inicia pipe de saldo e opção
    if (pipe(saldo_pipe) < 0 || pipe(key_pipe) < 0){
        printf("Erro ao criar pipe\n");
        exit(1);
    }
    

    // Escreve valor inicial de saldo
    int aux = 0;
    if (write(saldo_pipe[WRITE_POS], &aux, sizeof(int)) == -1){
        printf("Erro ao escrever no pipe\n");
        exit(1);
    }

    // Define primeiro fork
    pid_t pidParent  = getpid();
    pid_t firstChild = fork();

    // Tratamento de erro
    if (firstChild < 0){
        printf("Erro ao criar fork\n");
        exit(1);
    }
    fflush(stdin);

    // Define segundo fork
    pid_t secondChild = -1;
    if (getpid() == pidParent){
        secondChild = fork();

        if (secondChild < 0){
            exit(1);
        }

        if (secondChild == 0){
            firstChild = -1;
        }
    }
    
    // Le e imprime caso seja ramo principal
    if (getpid() == pidParent){
        int value;
        while(option != 107){
            do{
                option = (int)getchar();
            }while((option != 43) && (option != 115) && (option != 107) && (option != 45));

            // Imprime saldo
            if (option == 115){
                read(saldo_pipe[READ_POS], &value, sizeof(int));
                write(saldo_pipe[WRITE_POS], &value, sizeof(int));

                printf("\n=======================================\n");
                printf("|-> Mostrando Saldo no PID : %d\n", getpid());
                printf("|-> Saldo em conta         : %d UD\n", value);
                printf("=======================================\n");
            }
            // Escreve no pipe opção de operação (+-)
            else{
                write(key_pipe[WRITE_POS], &option, sizeof(int));
            }

            // Mata processos
            if (option == 107 || option == 75){
                printf("\n=======================================\n");
                printf("|-> Terminando (kill) Processos ... OK\n");
                printf("=======================================\n");

                kill(firstChild, SIGKILL);
                kill(secondChild, SIGKILL);
                kill(getpid(), SIGKILL);
                exit(0);
            }
        }
    }

    // Executa operação do primeiro fork (+)
    else if (firstChild == 0){
        int operacao;
        int value;

        do{
            read(key_pipe[READ_POS], &operacao, sizeof(int));

            if (operacao == 43){
                printf("\n|-> Adicionando 100 UD com PID: %d\n", getpid());

                read(saldo_pipe[READ_POS], &value, sizeof(int));
                value += 100;
                write(saldo_pipe[WRITE_POS], &value, sizeof(int));
            }
            else{
                write(key_pipe[WRITE_POS], &operacao, sizeof(int)); 
            }

        }while(operacao != 107);
    }
    // Executa operação do primeiro fork (-)
    else if (secondChild == 0){
        int operacao;
        int value;

        do{
            read(key_pipe[READ_POS], &operacao, sizeof(int));

            if(operacao == 45){
                printf("\n|-> Removendo 50 UD com PID: %d\n", getpid());

                read(saldo_pipe[READ_POS], &value, sizeof(int));
                value -= 50;
                write(saldo_pipe[WRITE_POS], &value, sizeof(int));
            }
            else{
                write(key_pipe[WRITE_POS], &operacao, sizeof(int)); 
            }
        
        }while(operacao != 107);
    }
    
        
    system ("/bin/stty cooked");

    return 0;
}

void display(int saldo){
    printf("==================================================\n");
    printf("# [+] - Utilizado para adicionar 100 UD ao saldo #\n");
    printf("# [-] - Utilizado para retirar 50 UD do saldo    #\n");
    printf("# [s] - Utilizado para imprimir o saldo          #\n");
    printf("# [k] - Utilizado para matar as thread criadas   #\n");
    printf("==================================================\n\n");
    printf("# Valor Inicial de Saldo: %d\n\n", saldo);
}