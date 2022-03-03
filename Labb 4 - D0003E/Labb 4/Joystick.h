#ifndef _JOYSTICK_
#define _JOYSTICK_

#include "TinyTimber.h"
#include "GUI.h"

#define initJoystick() {initObject()}

typedef struct {
	Object super;
} Joystick;

void direction();
void switch();
void hold();
void button();

#endif _JOYSTICK_