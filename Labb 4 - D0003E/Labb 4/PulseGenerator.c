#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "PulseGenerator.h"

void increase(Pulsegen *self){
	if (self->currentFreq < 99 && self->currentFreq >= 0){
		self->currentFreq++;
	}
	createpulse(self);
}

void decrease(Pulsegen *self){
	if (self->currentFreq <=99 && self->currentFreq > 0){
		self->currentFreq--;

	}
	createpulse(self);
}


void stored(Pulsegen *self){
	if(self->currentFreq != 0){
		self->storedFreq = self->currentFreq;
		self->currentFreq = 0;
	}
	else{
		self->currentFreq = self->storedFreq;
	}
	createpulse(self);
}

int getfreq(Pulsegen *self){	
	return(self->currentFreq);
}

void createpulse(Pulsegen *self){
	self->writer->freq = self->currentFreq;
	if(self->writer->freq != 0){
		if (self->writer->generateflag == 0){
			self->writer->generateflag = 1;
			self->writer->freq = self->currentFreq;
			AFTER(MSEC(100), self->writer, generateFreq, NULL);
		}
	}
	else{
		self->writer->generateflag = 0;
	}
}
