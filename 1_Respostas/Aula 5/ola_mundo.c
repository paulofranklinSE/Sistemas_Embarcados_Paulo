#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
int fp;	
char string[100] = "Ola mundo!";
int i=0;
fp = open("ola_mundo.txt", O_WRONLY | O_CREAT , S_IRWXU);
	if(fp==-1)
	{
		printf("Erro na abertura do arquivo.\n");
		exit(-1);
	}
  write (fp, &(string), 10);
close(fp);
return 0;
}
