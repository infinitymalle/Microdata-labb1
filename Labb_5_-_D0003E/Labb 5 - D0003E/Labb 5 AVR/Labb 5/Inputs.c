#include "Inputs.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#define bit0 (1 << 0) // North car arrive
#define bit1 (1 << 1) // North bridge entry
#define bit2 (1 << 2) // South car arrive
#define bit3 (1 << 3) // South bridge entry



void newcar(Inputs *self){
	while( ! (UCSR0A & (1 << RXC0)));
	volatile uint8_t putin = UDR0;
	
	// & "and" för varje bit
	if (putin & bit0){
		ASYNC(self->bridge, addcar, bit0);
	}else if((putin & bit1) || (putin & bit3)){
		ASYNC(self->bridge, carRun, NULL);
	}else if(putin & bit2){
		ASYNC(self->bridge, addcar, bit2);
	}
	//putin = 0;
}