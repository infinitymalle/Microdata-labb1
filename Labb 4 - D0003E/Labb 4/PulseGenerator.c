#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "PulseGenerator.h"

void increase(Pulsegen *self){
	if (self->currentFreq < 99 && self->currentFreq >= 0){
		self->currentFreq++;
	}
	ASYNC(self->writer, setFreq, self->currentFreq);
	ASYNC(self, createpulse, NULL);
}

void decrease(Pulsegen *self){
	if (self->currentFreq <=99 && self->currentFreq > 0){
		self->currentFreq--;

	}
	ASYNC(self->writer, setFreq, self->currentFreq);
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
//  	if(SYNC(self->writer, getGenFlag, NULL) == 0){
//  		createpulse(self);
//  	}
	ASYNC(self->writer, setFreq, self->currentFreq);
	ASYNC(self, createpulse, NULL);
}

int getfreq(Pulsegen *self){	
	return(self->currentFreq);
}


void createpulse(Pulsegen *self){
if(SYNC(self->writer, getGenFlag, NULL) == 0){
	ASYNC(self->writer, setFreq, self->currentFreq);
	ASYNC(self->writer, generateFreq, NULL);
	}
}