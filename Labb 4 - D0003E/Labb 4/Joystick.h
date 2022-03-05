#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#include "TinyTimber.h"
#include "GUI.h"
#include "PulseGenerator.h"

#define initJoystick() {initObject()}

typedef struct {
	Object super;
	Pulse *pulse;
	GUI *gui;
} Joystick;

void direction(Joystick *self);
void switchGen(Joystick *self);
void hold(Joystick *self);
void button(Joystick *self);

#endif JOYSTICK_H_