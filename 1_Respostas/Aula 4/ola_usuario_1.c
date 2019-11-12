#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
FILE *fp;
char nome[100];
char idade[4];
char frase[200] = "Nome: ";
char idade_frase[200] = "Idade: ";
int i=0;
fp = fopen("Eu.txt", "w");

if(!fp)
{
  //Arquivo ASCII, para escrita
  printf("Erro na leitura do arquivo");
  exit(0);
}

printf("Digite seu nome:");
gets(nome);
strcat(frase,nome);
printf("Digite sua idade:");
gets(idade);
strcat(idade_frase, idade);
for(i=0; frase[i]; i++)
  putc(frase[i],fp);
putc('\n',fp);
for(i=0; idade_frase[i]; i++)
  putc( idade_frase[i],fp);
fclose(fp);
return 0;
}
