#ifndef BRIDGE_H_
#define BRIDGE_H_

#include <avr/io.h>
//#include "Pinwriter.h"

#define initBridge() {initObject()}

typedef struct {
	Object super;
	int carsOnBridge;
	int queueLeft;
	int queueRight;
	int leftLight;
	int rightLight;
	
} Bridge;

void changeDirection(Bridge *self);

#endif