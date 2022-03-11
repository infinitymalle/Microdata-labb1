#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "PulseGenerator.h"

void increase(Pulsegen *self){
	if (self->currentFreq < 99 && self->currentFreq >= 0){
		self->currentFreq++;
	}
	ASYNC(self, createpulse, NULL);
}

void decrease(Pulsegen *self){
	if (self->currentFreq <=99 && self->currentFreq > 0){
		self->currentFreq--;

	}
	ASYNC(self, createpulse, NULL);
}


void stored(Pulsegen *self){
	if(self->currentFreq != 0){
		self->storedFreq = self->currentFreq;
		self->currentFreq = 0;
	}
	else{
		self->currentFreq = self->storedFreq;
	}
	ASYNC(self, createpulse, NULL);
}

void generateFreq(Pulsegen *self){
	if(self->currentFreq != 0){
		ASYNC(self->writer, togglepin, self->pin);
		AFTER(USEC(500000/self->currentFreq), self, generateFreq, NULL);
		self->generateflag = 1;
		}else{
		ASYNC(self->writer, pinzero, self->pin);
		self->generateflag = 0;
	}
}
int getfreq(Pulsegen *self){
	return(self->currentFreq);
}


void createpulse(Pulsegen *self){
if(self->generateflag == 0){
	ASYNC(self, generateFreq, NULL);
	}
}
 
 void toggleGenFlag(Pulsegen *self){
	 self->generateflag = !self->generateflag;
 }