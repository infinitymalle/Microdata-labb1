#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "PulseGenerator.h"

void increase(Pulsegen *self){
	if (self->currentFreq < 99 && self->currentFreq >= 0){
		self->currentFreq++;
	}
// 	if(SYNC(self->writer, getGenFlag, NULL) == 0){
// 		createpulse(self);
// 	}
	createpulse(self);
}

void decrease(Pulsegen *self){
	if (self->currentFreq <=99 && self->currentFreq > 0){
		self->currentFreq--;

	}
//  	if(SYNC(self->writer, getGenFlag, NULL) == 0){
//  		createpulse(self);
//  	}
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
//  	if(SYNC(self->writer, getGenFlag, NULL) == 0){
//  		createpulse(self);
//  	}
	createpulse(self);
}

int getfreq(Pulsegen *self){	
	return(self->currentFreq);
}


void createpulse(Pulsegen *self){
	/*self->writer->freq = self->currentFreq;*/
	
	if(self->currentFreq != 0){
// 		if (SYNC(self->writer, getGenFlag, NULL) == 0){
// 			ASYNC(self->writer, setGenFlag, NULL);
// 			ASYNC(self->writer, setFreq, self->currentFreq);
// 			
// 		}
		ASYNC(self->writer, setFreq, self->currentFreq);
		AFTER(USEC(500000/self->currentFreq), self->writer, generateFreq, NULL);
	}
}