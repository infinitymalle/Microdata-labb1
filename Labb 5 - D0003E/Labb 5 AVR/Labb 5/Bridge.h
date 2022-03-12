#ifndef BRIDGE_H_
#define BRIDGE_H_

#include <avr/io.h>
#include "GUI.h"

#define initBridge(carsOnBridge, queueSouth, queueNorth, southLight, northLight, carspassde, gui) {initObject(),carsOnBridge, queueSouth, queueNorth, southLight, northLight, carspassde, gui}

typedef struct {
	Object super;
	int carsOnBridge;
	int queueSouth;
	int queueNorth;
	int southLight;
	int northLight;
	int carspassde;
	GUI *gui;
} Bridge;

void addcar(Bridge *self, int fromDirection);
void changeDirection(Bridge *self);
void carRun(Bridge *self);
void carLeave(Bridge *self);
void changeSouth(Bridge *self);
void changeNorth(Bridge *self);
void updateDisp(Bridge *self);

#endif