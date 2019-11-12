#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
int fp;
char nome[100];
char idade[4];
char frase[200] = "Nome: ";
char idade_frase[200] = "Idade: ";
int i=0;

fp = open(argv[1], O_WRONLY | O_CREAT , S_IRWXU);
if(fp==-1)
	{
		printf("Erro na abertura do arquivo.\n");
		exit(-1);
	}


