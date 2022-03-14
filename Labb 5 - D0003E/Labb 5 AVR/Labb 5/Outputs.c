#include "Outputs.h"

void transmit(Outputs *self, int lightStatus){
	if (lightStatus == 0){
		self->data = 0b1001;
	}
	else if(lightStatus == 1){
		self->data = 0b0110;
	}else{
		self->data = 0b1010;
	}
	
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = self->data;
}



//röd röd kön > andra kön 
//röd grön // kön > 0 && (tillräckligt många bilar inte passerat ännu || andra kön är tom)
//grön röd