#ifndef INPUTS_H_
#define INPUTS_H_

#include <avr/io.h>
#include "Bridge.h"

#define southcar 0x73
#define northcar 0x6E
#define exit 0x65
#define initInputs(bridge) {initObject(), bridge}

typedef struct {
	Object super;
	
	Bridge *bridge;
} Inputs;
void USART_Init(unsigned int ubrr);
void newcar(Inputs *self);
	

#endif