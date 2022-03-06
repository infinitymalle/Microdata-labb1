#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#include <avr/io.h>
#include "Gui.h"

#define initJoystick(gui) {initObject(), gui};

typedef struct {
	Object super;
	GUI *gui;
} Joystick;

void button_Init();
void direction(Joystick *self);		//upp, ner eller tryck
void changepulsegenerator(Joystick *self);	//höger eller vänster

#endif