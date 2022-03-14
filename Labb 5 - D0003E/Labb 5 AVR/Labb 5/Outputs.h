#ifndef OUTPUTS_H_
#define OUTPUTS_H_

#include <avr/io.h>
#include "TinyTimber.h"

#define initOutputs(data) {initObject(), 0}

typedef struct {
	Object super;
	int data;
} Outputs;

void transmit(Outputs *self, int data);

#endif