#ifndef BRIDGE_H_
#define BRIDGE_H_

#include <avr/io.h>
#include "GUI.h"
#include "Outputs.h"

#define initBridge(carsOnBridge, queueSouth, queueNorth, southLight, northLight, carspassed, firstcar, gui, outputs) {initObject(),carsOnBridge, queueSouth, queueNorth, southLight, northLight, carspassed, firstcar, gui, outputs}

typedef struct {
	Object super;
	int carsOnBridge;
	int queueSouth;
	int queueNorth;
	int southLight;
	int northLight;
	int carspassed;
	int firstcar;
	GUI *gui;
	Outputs *outputs;
} Bridge;

void addcar(Bridge *self, int sensor);
void setNorth(Bridge *self);
void setSouth(Bridge *self);
void changeDirection(Bridge *self);
void stop(Bridge *self);
void carRun(Bridge *self);
void carLeave(Bridge *self);
void changeSouth(Bridge *self);
void changeNorth(Bridge *self);
void updateDisp(Bridge *self);

void leaveChange(Bridge *self, int fromSouth);

#endif