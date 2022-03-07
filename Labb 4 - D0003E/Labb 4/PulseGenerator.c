#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "PulseGenerator.h"

void increase(Pulsegen *self){
	if (self->currentFreq < 99 && self->currentFreq >= 0){
		self->currentFreq++;
		//int i = 1;
		//while(i != 0){
			//i++;
			//if(((PINB >> 6) & 1) == 0){
				//AFTER(MSEC(100), self, increase, NULL);
			//}else{
				//i = 0;
			//}
		//}
	}
}

void decrease(Pulsegen *self){
	if (self->currentFreq <=99 && self->currentFreq > 0){
		self->currentFreq--;
		//int i = 1;
		//while(i != 0){
			//i++;
			//if(((PINB >> 7) & 1) == 0){
				//AFTER(MSEC(100), self, decrease, NULL);
			//}else{
				//i = 0;
			//}
		//}
	}
}


void stored(Pulsegen *self){
	if(self->currentFreq != 0){
		self->storedFreq = self->currentFreq;
		self->currentFreq = 0;
	}
	else{
		self->currentFreq = self->storedFreq;
	}
}
int getfreq(Pulsegen *self){
	return(self->currentFreq);
}