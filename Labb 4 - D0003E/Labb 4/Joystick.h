#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#include "TinyTimber.h"
#include "PulseGenerator.h"
#include "Porthandler.h"

#define initJoystick(Pulse *port) {initObject(), Pulse *port}

typedef struct {
	Object super;
	Pulse *pulse;
	Pulsegen *pulsegen;
} Joystick;

void direction(Joystick *self);		//upp, ner eller tryck
void changepulsegenerator(Joystick *self);	//h�ger eller v�nster

#endif JOYSTICK_H_