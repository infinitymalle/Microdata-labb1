#include "Outputs.h"


void transmit(Outputs *self, int lightStatus){
	if (lightStatus == 0){
		self->data = 0b1001;	// north Green south Red
	}
	else if(lightStatus == 1){ 
		self->data = 0b0110;	// north Red south Green
	}else if (lightStatus == 2){
		self->data = 0b1010;	// Red Red
	}
	
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = self->data;
	self->data = 0;
}