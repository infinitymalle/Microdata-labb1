#ifndef PULSEGEN_H_
#define PULSEGEN_H_

#include <avr/io.h>
#include "Pinwriter.h"

#define initPulsegen(currentFreq, storedFreq, pin, generateflag, writer) {initObject(), currentFreq, storedFreq, pin, 0, writer}
	
typedef struct {
	Object super;
	int currentFreq;	// Nuvarande frekvens
	int storedFreq;		// Sparad frekvens
	int pin;
	int generateflag;
	Writer *writer;
} Pulsegen;

void increase(Pulsegen *self);
void decrease(Pulsegen *self);
void stored(Pulsegen *self);
int getfreq(Pulsegen *self);
void createpulse(Pulsegen *self);
void toggleGenFlag(Pulsegen *self);
int getGenFlag(Pulsegen *self);

#endif