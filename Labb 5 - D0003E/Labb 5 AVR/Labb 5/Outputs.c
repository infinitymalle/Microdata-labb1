#include "Outputs.h"

void transmit(Outputs *self, int lightStatus){
	if (lightStatus == 0){
		data = 0b0110;
	}
	else if(lightStatus == 1){
		data = 0b1001;
	}
	
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;
}