#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

struct vetor_media
{
	long int vetor[50000];
	double media1;
	double media2;
	double media3;	
	double media4;
};



void* search1(void *v)
{
	struct vetor_media* p = (struct vetor_media*) v; 
	int i;
	long int soma=0;
	p->media1=0;

	//maiores[0] = vetor[0];

	for(i=0;i<12500;i++)
	{

		soma=soma+p->vetor[i];
	}

	p->media1 = ((double)soma)/12500;
	v =  p;
}
void* search2(void *v)
{
	struct vetor_media* p = (struct vetor_media*) v; 
	int i;
	long int soma=0;
	p->media2=0;

	//maiores[0] = vetor[0];

	for(i=12500;i<25000;i++)
	{

		soma=soma+p->vetor[i];
	}

	p->media2 = ((double)soma)/12500;
	v =  p;
}
void* search3(void *v)
{
	struct vetor_media* p = (struct vetor_media*) v; 
	int i;
	long int soma=0;
	p->media3=0;

	//maiores[0] = vetor[0];

	for(i=25000;i<37500;i++)
	{

		soma=soma+p->vetor[i];
	}

	p->media3 = ((double)soma)/12500;
	v =  p;
}
void* search4(void *v)
{
	struct vetor_media* p = (struct vetor_media*) v; 
	int i;
	long int soma=0;
	p->media4=0;
	//maiores[0] = vetor[0];

	for(i=37500;i<50000;i++)
	{

		soma=soma+p->vetor[i];
	}

	p->media4 = ((double)soma)/12500;
	v =  p;
}




double calcula_media(long int *v)
{
	long int soma = 0;
	double media_funcao=0;
	int i;

	for(i=0;i<50000;i++)
	{
		soma += v[i];	
	}
	
	media_funcao = ((double)soma) /50000.00;
	return media_funcao;
}

int main ()
{
	
	long int v[50000];
	int i;
	double media_total=0;
	double media_total2=0;
	pthread_t thread_id1;
	pthread_t thread_id2;
	pthread_t thread_id3;
	pthread_t thread_id4;
	struct vetor_media a; 

	//criando vetor

	for(i=0;i<50000;i++)
	{
		v[i]= random();
		a.vetor[i] = v[i];
	}

	pthread_create(&thread_id1, NULL,&search1,&a);
	pthread_create(&thread_id2, NULL,&search2,&a);
	pthread_create(&thread_id3, NULL,&search3,&a);
	pthread_create(&thread_id4, NULL,&search4,&a);
	pthread_join(thread_id1,NULL);
	pthread_join(thread_id2,NULL);
	pthread_join(thread_id3,NULL);
	pthread_join(thread_id4,NULL);

	printf("Media por thread1: %.2lf\n",a.media1);
	printf("Media por thread1: %.2lf\n",a.media2);
	printf("Media por thread1: %.2lf\n",a.media3);
	printf("Media por thread1: %.2lf\n",a.media4);

	media_total= a.media1 + a.media2 + a.media3 + a.media4;
	media_total = media_total/4;
	
	printf("Media final por thread: %.2lf\n",media_total);
	//valor da busca completa


	media_total2 = calcula_media(v);
	
	printf("Media por busca completa: %.2lf\n",media_total2);


	return 0;
}