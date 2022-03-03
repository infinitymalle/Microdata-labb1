#ifndef PULSEGEN_H_
#define PULSEGEN_H_

#include "TinyTimber.h"
#include "Gui.h"
#include "Joystick.h"

#define initPulse() {initObject()}
	
typedef struct {
	Object super;
	int currentFreq;
	int storedFreq;
	int port;
} Pulse;

void increase(Pulse *self);
void decrease(Pulse *self);
void stored(Pulse *self);

#endif PULSEGEN_H_