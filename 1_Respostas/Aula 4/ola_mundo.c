#include <stdio.h>
#include <stdlib.h>

int main()
{
FILE *fp;
char string[100] = "Ola mundo!";
int i=0;
fp = fopen("ola_mundo.txt", "w");

if(!fp)
{
  //Arquivo ASCII, para escrita
  printf("Erro na leitura do arquivo");
  exit(0);
}

for(i=0; string[i]; i++)
  putc(string[i],fp);
fclose(fp);
return 0;
}
