#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "pinwriter.h"


void generateFreq(Writer *self){
	if(self->freq != 0){
		PINE ^= 1 << self->pin;
		AFTER(USEC(500000/self->freq), self, generateFreq, NULL);
	}
 	else{
	 	self->generateflag = 0;
 	}
}

int getGenFlag(Writer *self){
	return(self->generateflag);
}
void setGenFlag(Writer *self){
	self->generateflag = !self->generateflag;
}

void setFreq(Writer *self){
	SYNC
}