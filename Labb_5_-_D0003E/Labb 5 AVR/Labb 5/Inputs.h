#ifndef INPUTS_H_
#define INPUTS_H_

#include <avr/io.h>
#include "Bridge.h"


#define initInputs(bridge) {initObject(), bridge}

typedef struct {
	Object super;
	
	Bridge *bridge;
} Inputs;
void USART_Init(unsigned int ubrr);
void newcar(Inputs *self);
	

#endif