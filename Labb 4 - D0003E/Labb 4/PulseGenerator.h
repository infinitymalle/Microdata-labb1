#ifndef PULSEGEN_H_
#define PULSEGEN_H_

#include <avr/io.h>
#include "Pinwriter.h"

#define initPulsegen(currentFreq, storedFreq, writer) {initObject(), currentFreq, storedFreq, writer}
	
typedef struct {
	Object super;
	int currentFreq;	// Nuvarande frekvens
	int storedFreq;		// Sparad frekvens
	Writer *writer;
} Pulsegen;

void increase(Pulsegen *self);
void decrease(Pulsegen *self);
void stored(Pulsegen *self);
int getfreq(Pulsegen *self);
void createpulse(Pulsegen *self);


#endif