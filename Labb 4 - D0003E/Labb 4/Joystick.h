#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#include "TinyTimber.h"
#include "GUI.h"
#include "PulseGenerator.h"

#define initJoystick() {initObject()}

typedef struct {
	Object super;
} Joystick;

void direction();
void switch();
void hold();
void button();

#endif JOYSTICK_H_