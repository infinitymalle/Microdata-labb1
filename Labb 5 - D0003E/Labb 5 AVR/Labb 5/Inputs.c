#include "Inputs.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>

#define FOCS 8000000
#define BAUD 9600
#define MYUBRR (FOCS/16/BAUD-1)

void USART_Init(unsigned int ubrr){
	UBRR0H = (unsigned char) (ubrr>>8);
	UBRR0L = (unsigned char) ubrr;
	
	UCSR0B = (1 << TXEN0) | (1 << RXCIE0) | (1 << RXEN0);
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
	
}

void newcar(Inputs *self){
	while( ! (UCSR0A & (1 << RXC0)));
	if((UDR0 == southcar) || (UDR0 == northcar)){
		int putin = UDR0;
		ASYNC(self->bridge, addcar, putin);
	}
	else if(UDR0 == exit){
		while(1){}
	}
}