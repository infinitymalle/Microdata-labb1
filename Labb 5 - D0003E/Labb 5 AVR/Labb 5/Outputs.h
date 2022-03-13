#ifndef OUTPUTS_H_
#define OUTPUTS_H_

#include <avr/io.h>
#define data = 0

#define initOutputs() {initObject()}

typedef struct {
	Object super;
} Outputs;

void transmit(Outputs *self, unsigned char data);


#endif