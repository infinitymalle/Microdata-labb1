#ifndef OUTPUTS_H_
#define OUTPUTS_H_

#include <avr/io.h>

#define initInputs() {initObject()}

typedef struct {
	Object super;
} Inputs;
void USART_Init(unsigned int ubrr);
void newcar(Inputs *self);


#endif