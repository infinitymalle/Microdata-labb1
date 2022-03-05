#ifndef PULSEGEN_H_
#define PULSEGEN_H_

#include "TinyTimber.h"
#include "Gui.h"
#include "Joystick.h"

#define initPulsegen() {initObject(), 0, 0, 1}
	
typedef struct {
	Object super;
	int currentFreq;	// Nuvarande frekvens
	int storedFreq;		// Sparad frekvens
	int port;			// Höger eller vänster
} Pulsegen;

void increase(Pulsegen *self);
void decrease(Pulsegen *self);
void stored(Pulsegen *self);
void changedisplaysegment(Pulsegen *self); 
void generate(Pulsegen *self);	// Genererar pulser

#endif PULSEGEN_H_