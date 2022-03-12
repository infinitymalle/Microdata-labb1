#ifndef OUTPUTS_H_
#define OUTPUTS_H_

#include <avr/io.h>

#define initOutputs() {initObject()}

typedef struct {
	Object super;
} Outputs;

void (Outputs *self);


#endif