#ifndef PULSEHANDLER_H_
#define PULSEHANDLER_H_

#include "TinyTimber.h"
#include "GUI.h"
#include "Joystick.h"

#define initPulse(Pulsegen *pulse1, Pulsegen *pulse2) {initObject(), 0}

typedef struct {
	Object super;
	int focus; // 1 blir vänster o blir höger
	Pulsegen pulse1;
	Pulsegen pulse2;
} Pulse;

void changefocus(Pulse *self, int newfocus);
void updategui(Pulse *self);
#endif PULSEHANDLER_H_