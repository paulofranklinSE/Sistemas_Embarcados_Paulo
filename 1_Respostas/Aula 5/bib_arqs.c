#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "bib_arqs.h"

int tam_arq_texto(char *nome_arquivo)
{
int fp;
int i=0;
fp = open(nome_arquivo, O_WRONLY | O_CREAT , S_IRWXU);
char ch;
int tamanho=0;
if(fp==-1)
	{
		printf("Erro na abertura do arquivo.\n");
		exit(-1);
	}


while (read (fp, &ch, sizeof(ch))!= 0)
	{
  	tamanho++;
	}
close(fp);

return tamanho;
}

void le_arq_texto (char *nome_arquivo, char *conteudo) {
int fp;
fp = open(nome_arquivo, O_RDONLY | O_CREAT , S_IRWXU);
char ch;
int tamanho=0;

if(fp==-1)
	{
		printf("Erro na abertura do arquivo.\n");
		exit(-1);
	}


while (read (fp, &ch, sizeof(ch))!= 0)
	{
	conteudo[tamanho]=ch;
  	tamanho++;

	}
close(fp);
}

