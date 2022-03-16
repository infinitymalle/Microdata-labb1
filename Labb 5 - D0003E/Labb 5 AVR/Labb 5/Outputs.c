#include "Outputs.h"


void transmit(Outputs *self, int lightStatus){
	if (lightStatus == 0){
		self->data = 0x6;	// north Green south Red 0b0110
	}
	else if(lightStatus == 1){ 
		self->data = 0x9;	// north Red south Green 0b1001
	}else if (lightStatus == 2){
		self->data = 0xA;	// Red Red 0b1010
	}
	
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = self->data;
	self->data = 0;
}