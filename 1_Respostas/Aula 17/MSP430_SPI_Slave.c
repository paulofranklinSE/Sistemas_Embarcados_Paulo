#include <msp430g2553.h>
#include <legacymsp430.h>

#define AD_IN BIT0
#define AD_INCH INCH_0
#define MISO BIT1
#define MOSI BIT2
#define SCLK BIT4
#define LED  BIT6

void Send_Data(volatile unsigned char c)
{
	while((IFG2&UCA0TXIFG)==0);
	UCA0TXBUF = c;
}

int main(void)
{
	WDTCTL = WDTPW + WDTHOLD;
	BCSCTL1 = CALBC1_16MHZ;
	DCOCTL = CALDCO_16MHZ;
	P1SEL2 = P1SEL = MOSI+MISO+SCLK;
	P1OUT &= ~LED;
	P1DIR |= LED;

	ADC10AE0  = AD_IN;
	ADC10CTL0 = SREF_0 + ADC10SHT_0 + ADC10IE + ADC10ON;
	ADC10CTL1 = AD_INCH + SHS_0 + ADC10DIV_0 + ADC10SSEL_3 + CONSEQ_0;

	UCA0CTL1 = UCSWRST;
	UCA0CTL0 = UCCKPH + UCMSB + UCMODE_0 + UCSYNC;
	UCA0CTL1 &= ~UCSWRST;
	Send_Data(0xAA);
	IE2 |= UCA0RXIE;
	
	_BIS_SR(LPM0_bits + GIE);
	return 0;
}

interrupt(USCIAB0RX_VECTOR) Receive_Data(void)
{
	static unsigned int d = 1023;
	if(UCA0RXBUF==0x55)
	{
		P1OUT |= LED;
		ADC10CTL0 |= ENC+ADC10SC;
		while( (ADC10CTL0 & ADC10IFG) == 0);
		d = ADC10MEM;
		//d=1023;
		Send_Data(d & 0xff);
	}
	else if(UCA0RXBUF==0x01)
	{
		Send_Data(d>>8);
	}
	else if(UCA0RXBUF==0x02)
	{
		Send_Data(0xAA);
		P1OUT &= ~LED;
	}
/*	else
	{
		P1OUT |= LED;
		d = 0x3ff;
		while(d--);
		P1OUT &= ~LED;
	}*/
	IFG2 &= ~UCA0RXIFG;
}