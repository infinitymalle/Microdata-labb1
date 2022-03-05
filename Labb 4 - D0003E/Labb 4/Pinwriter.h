#ifndef PINWRITER_H_
#define PINWRITER_H_

#include "TinyTimber.h"
#include "Gui.h"
#include "Joystick.h"

#define initWriter() {initObject(), 0}

typedef struct {
	Object super;
	int left;
	
} Writer;

void focus(Port, *self);
#endif PINWRITER_H_