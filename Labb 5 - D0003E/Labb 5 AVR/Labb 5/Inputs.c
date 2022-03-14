#include "Inputs.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#define bit1 (1 << 0)
#define bit2 (1 << 1)
#define bit3 (1 << 2)
#define bit4 (1 << 3)



void newcar(Inputs *self){
	while( ! (UCSR0A & (1 << RXC0)));
	volatile uint8_t putin = UDR0;
	
	if (putin & bit1){
		ASYNC(self->bridge, addcar,bit1);
	}else if(putin & bit2){
		ASYNC(self->bridge, addcar,bit2);
	}else if(putin & bit3){
		ASYNC(self->bridge, addcar,bit3);
	}else if(putin & bit4){
		ASYNC(self->bridge, addcar,bit4);
	}
	
	//if((UDR0 == 0x4) || (UDR0 == 0x1) || (UDR0 == 0x8) || (UDR0 == 0x2)){
		//int putin = UDR0;	
		//ASYNC(self->bridge, addcar, putin);
	//}
	
	
}