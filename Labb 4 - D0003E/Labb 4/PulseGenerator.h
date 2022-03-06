#ifndef PULSEGEN_H_
#define PULSEGEN_H_

#include <avr/io.h>
#include "TinyTimber.h"

#define initPulsegen(currentFreq, storedFreq) {initObject(), currentFreq, storedFreq}
	
typedef struct {
	Object super;
	int currentFreq;	// Nuvarande frekvens
	int storedFreq;		// Sparad frekvens
} Pulsegen;

void increase(Pulsegen *self);
void decrease(Pulsegen *self);
void stored(Pulsegen *self);
int getfreq();

#endif