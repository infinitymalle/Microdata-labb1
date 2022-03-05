#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "PulseGenerator.h"

void increase(Pulse *self){
	if (self->currentFreq < 99 && self->currentFreq >= 0){
		self->currentFreq++;
	}
}

void decrease(Pulse *self){
	if (self->currentFreq <=99 && self->currentFreq > 0){
		self->currentFreq--;
	}
}

void stored(Pulse *self){
	if(self->currentFreq != 0){
		self->storedFreq = self->currentFreq;
		self->currentFreq = 0;
	}
	else{
		self->currentFreq = self->storedFreq;
	}
}

void generate(Pulse *self){
	
}