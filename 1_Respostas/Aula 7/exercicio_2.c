#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>


int main()
{
    pid_t pid_filho;
    int fd[2];
    
    pipe(fd);
    pid_filho = fork();

    // Codigo do filho    
    if(pid_filho == 0)
    {
        
        char buf_filho[100];

        //sleep(1);

        strcpy(buf_filho,"Pai, qual � a verdadeira ess�ncia da sabedoria?");

        if (write(fd[1], buf_filho, sizeof(buf_filho)) < 0)
        {
            printf("Erro na escrita do pipe\n");
        }

        sleep(1); 

        if(read(fd[0], buf_filho, 100) < 0) 
        {
            printf("Erro na leitura do pipe\n");
        }
        else
        {
            printf("Pai = %s\n", buf_filho);
        }

        strcpy(buf_filho,"Mas at� uma crian�a de tr�s anos sabe disso!");

        if (write(fd[1], buf_filho, sizeof(buf_filho)) < 0)
        {
            printf("Erro na escrita do pipe\n");
        }

        sleep(1);

        if(read(fd[0], buf_filho, 100) < 0) 
        {
            printf("Erro na leitura do pipe\n");
        }
        else
        {
            printf("Pai = %s\n", buf_filho);
        }


    }
    
    // Codigo do pai
    else
    {
        char buf_pai[100];


        if(read(fd[0], buf_pai, 100) < 0) 
        {
            printf("Erro na leitura do pipe\n");
        }
        else
        {
            printf("Filho = %s\n", buf_pai);
        }

        strcpy(buf_pai,"N�o fa�ais nada violento, praticai somente aquilo que � justo e equilibrado.");

        if (write(fd[1], buf_pai, sizeof(buf_pai)) < 0)
        {
            printf("Erro na escrita do pipe\n");
        }

        sleep(2); 

        if(read(fd[0], buf_pai, 100) < 0) 
        {
            printf("Erro na leitura do pipe\n");
        }
        else
        {
            printf("Filho = %s\n", buf_pai);
        }

        strcpy(buf_pai,"Sim, mas � uma coisa dif�cil de ser praticada at� mesmo por um velho como eu...");

        if (write(fd[1], buf_pai, sizeof(buf_pai)) < 0)
        {
            printf("Erro na escrita do pipe\n");
        }

    }
    sleep(2);
    return 0;
}
