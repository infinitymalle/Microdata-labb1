#ifndef PULSEHANDLER_H_
#define PULSEHANDLER_H_

#include <avr/io.h>
#include "TinyTimber.h"
#include "Gui.h"
#include "PulseGenerator.h"
#include "Joystick.h"

#define initPulse(focus, pulse1, pulse2, gui) {initObject(), focus, pulse1, pulse2, gui}

typedef struct {
	Object super;
	int focus; // 1 blir vänster, 0 blir höger
	Pulsegen *pulse1;
	Pulsegen *pulse2;
	GUI *gui;
} Pulse;

void changefocus(Pulse *self, int newfocus);
void updategui(Pulse *self);
#endif