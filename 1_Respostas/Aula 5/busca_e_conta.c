#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "num_caracs.h"
#include "bib_arqs.h"

int main(int argc, char *argv[])
{

char string[100]="";
int i=0;
int a=0;
int contador=0;
int tamanho_palavra=0;

tamanho_palavra = Num_Caracs(argv[1]);

le_arq_texto(argv[2],string);

for(i=0;string[i] != '\0' ;i++)
{
  if(string[i]==argv[1][a])
  {
     a++;
  }
  else if (string[i]!=argv[1][a])
  {
    a=0;
  }
  if (tamanho_palavra==a)
  {
    contador++;
   
    a=0;
  }
}
printf("'%s' ocorre %d vezes no arquivo '%s'\n",argv[1],contador,argv[2]);
return 0;

}                        

