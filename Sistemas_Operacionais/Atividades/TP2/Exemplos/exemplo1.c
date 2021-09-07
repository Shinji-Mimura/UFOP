#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void *myturn(void *arg)
{
    int *iptr = (int *)malloc(sizeof(int));
    *iptr = 5;
    for (int i = 0; i < 8; i++)
    {
        sleep(1);
        printf("My Turn %d\n", *iptr);
        (*iptr)++;
    }

    return iptr;
}

void yourturn()
{
    for (int i = 0; i < 3; i++)
    {
        sleep(2);
        printf("Your Turn\n");
    }
}

int main(int argc, char const *argv[])
{

    pthread_t newthread;
    int *result;

    pthread_create(&newthread, NULL, myturn, NULL);

    //myturn();
    yourturn();
    pthread_join(newthread, (void *)&result);

    printf("Value => %d\n", *result);

    return 0;
}
