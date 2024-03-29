#include <msp430g2452.h>
#include <legacymsp430.h>

#define AD_IN BIT0
#define AD_INCH INCH_0
#define RX BIT1
#define TX BIT2
#define BTN BIT3
#define LED BIT6

void Send_Data(volatile unsigned char c);

int main(void)
{
	WDTCTL = WDTPW + WDTHOLD;
	
	BCSCTL1 = CALBC1_1MHZ;
	DCOCTL = CALDCO_1MHZ;
	
	P1OUT |= BTN;
	P1REN |= BTN;
	P1DIR &= ~BTN;
	P1IE = P1IES = BTN;
	P1OUT &= ~LED;
	P1DIR |= LED;

	TACCR0 = 10000-1;
	TACCR1 = TACCR0/2;
	TACCTL1 = OUTMOD_7;
	TACTL = TASSEL_2 | ID_0 | MC_1;
	
	ADC10AE0  = AD_IN;
	ADC10CTL0 = SREF_0 + ADC10SHT_0 + ADC10IE + ADC10ON;
	ADC10CTL1 = AD_INCH + SHS_1 + ADC10DIV_0 + ADC10SSEL_3 + CONSEQ_2;
	ADC10CTL0 |= ENC;
	
	P1SEL2 = P1SEL = RX+TX;
	UCA0CTL0 = 0;
	UCA0CTL1 = UCSSEL_2;
	UCA0BR0 = 6;
	UCA0BR1 = 0;
	UCA0MCTL = UCBRF_8 + UCOS16;

	_BIS_SR(LPM0_bits+GIE);
	return 0;
}

interrupt(PORT1_VECTOR) P1_ISR(void)
{
	P1OUT |= LED;
	while((P1IN&BTN)==0);
	P1IFG &= ~BTN;
	P1OUT &= ~LED;
}

interrupt(ADC10_VECTOR) ADC10_ISR(void)
{
	static int i = 0;
	Send_Data(ADC10MEM & 0xff);
	Send_Data(ADC10MEM >> 8);
	ADC10CTL0 &= ~ADC10IFG;
	ADC10CTL0 |= ENC;
	if(i==49)
	{
		P1OUT ^= LED;
		i=0;
	}
	else i++;
}

void Send_Data(volatile unsigned char c)
{
	while((IFG2&UCA0TXIFG)==0);
	UCA0TXBUF = c;
}