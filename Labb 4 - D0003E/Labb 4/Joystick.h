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
void changepulsegenerator(Joystick *self);	//höger eller vänster

#endif JOYSTICK_H_