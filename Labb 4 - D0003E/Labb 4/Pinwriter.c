#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "pinwriter.h"


void togglepin(Writer *self, int pin){
	PORTE ^= (1 << pin);
}
void pinzero(Writer *self, int pin){
	PORTE &= ~(1 << pin);
}