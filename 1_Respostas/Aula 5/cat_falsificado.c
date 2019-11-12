#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "bib_arqs.h"
int main(int argc , char *argv[])
{
char string[200]="";

le_arq_texto(argv[1],string);

printf("%s",string);


return 0;
}
