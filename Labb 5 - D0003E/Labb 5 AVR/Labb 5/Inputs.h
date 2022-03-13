#ifndef INPUTS_H_
#define INPUTS_H_

#include <avr/io.h>
#include "Bridge.h"

#define southcar 0b0100
#define southDrive 0b1000
#define northcar 0b0001
#define northDrive 0b0010
#define exit 0x65
#define initInputs(bridge) {initObject(), bridge}

typedef struct {
	Object super;
	
	Bridge *bridge;
} Inputs;
void USART_Init(unsigned int ubrr);
void newcar(Inputs *self);
	

#endif