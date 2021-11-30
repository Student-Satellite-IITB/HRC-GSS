#include <avr/io.h>
#include "UART.h"
#include <avr/interrupt.h>
#define F_CPU 16000000UL

void setUART()
{
	DDRD=0b00000010;
	UCSRA|=(1<<U2X);
	UBRRL=0b11001111; //Baud Rate=9600
	UBRRH=0x00;
	UCSRB= (1<<RXEN)|(1<<TXEN);
	UCSRC= (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);
}

uint8_t UARTReceive()
{
	while(!(UCSRA & (1<<RXC)));
	data8bit=UDR;
	return data8bit;
}