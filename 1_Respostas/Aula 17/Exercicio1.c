#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

// Arquivo de acesso a porta serial
//#define TTY "/dev/ttyAMA0"
// Arquivo de acesso a porta serial
// PARA O RASPBERRY PI 3
#define TTY "/dev/ttyS0"

int uart0_fd;

void ctrl_c(int sig)
{
	puts(" Fechando " TTY "...");
	close(uart0_fd);
	exit(-1);
}

int main(void)
{
	struct termios options;
	//char user_input, msp430_return=0;

	signal(SIGINT, ctrl_c);
	uart0_fd = open(TTY, O_RDWR); // | O_NOCTTY); // | O_NDELAY);
	if(uart0_fd==-1)
	{
		puts("Erro abrindo a UART. Garanta que ela nao esteja sendo usada por outra aplicacao.");
		return -1;
	}
	puts(TTY " aberto.");
	tcgetattr(uart0_fd, &options);
	options.c_cflag = CS8 | CREAD | CLOCAL;
	options.c_iflag = 0;
	options.c_oflag = 0;
	options.c_lflag = 0;
	options.c_cc[VTIME] = 0;
	options.c_cc[VMIN]  = 1;
	cfsetospeed(&options, B9600);
        cfsetispeed(&options, B9600);
	tcflush(uart0_fd, TCIOFLUSH);
	tcsetattr(uart0_fd, TCSANOW, &options);
	puts("UART configurada:");
	system("stty -F " TTY);
	puts("");
	//user_input = 1;
	while(1)
	{
		int i;
		int soma = 0;
		char string[100];
		for(i = 0; i < 100; i++)
		{
			read(uart0_fd, &string[i], sizeof(string[i]));
			soma = soma + string[i];
			usleep(10000);
			
		}
		media = soma/100;
			//if(read(uart0_fd, &msp430_return, 1)==1)
		sleep(1);
		printf("A media das 100 amostras e = %d\n", media);
			
		
		puts("");
	}
	close(uart0_fd);
}