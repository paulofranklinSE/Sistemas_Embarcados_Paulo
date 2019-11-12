#include <stdio.h>
#include <stdlib.h>
#include "bib_arqs.h"

int tam_arq_texto(char *nome_arquivo)
{

FILE *fp;
int i=0;
fp = fopen(nome_arquivo, "r");
char ch;
int tamanho=0;

if(!fp)
{
  //Arquivo ASCII, para escrita
  printf("Erro na leitura do arquivo");
  exit(0);
}

while (1)
{
  ch = fgetc(fp); 
  if(ch == EOF) //end of file 
    break;
  tamanho++;
}
fclose(fp);

return tamanho;

}

void le_arq_texto (char *nome_arquivo, char *conteudo)
{

FILE *fp;
int i=0;
fp = fopen(nome_arquivo, "r");
char ch;
int tamanho=0;

if(!fp)
{
  //Arquivo ASCII, para escrita
  printf("Erro na leitura do arquivo");
  exit(0);
}

while (1)
{
  ch = fgetc(fp);
  if(ch == EOF)
    break;
  
  conteudo[tamanho] = ch;
  tamanho++;
}
fclose(fp);

}
