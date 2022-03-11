#include "Bridge.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>

void changeDirection(Bridge *self){
	if (self->leftLight){
		self->leftLight = 0;
		AFTER(MSEC(5000), self, )
	}else if (self->rightLight){
		self->rightLight = 0;
		AFTER(MSEC(5000), self, )
	}
}

void carRun(Bridge *self){
	if((self->leftLight == 0) && (self->queueLeft != 0)){
		self->queueLeft--;
		self->carsOnBridge++;
		AFTER(MSEC(1000), self, carRun, NULL);
	}else if((self->rightLight == 1) && (self->queueRight != 0)){
		self->queueRight--;
		self->carsOnBridge++;
		AFTER(MSEC(1000), self, carRun, NULL);
	}
}