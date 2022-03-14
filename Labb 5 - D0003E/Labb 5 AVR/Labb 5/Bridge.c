#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "Bridge.h"


void addcar(Bridge *self, int sensor){
	if (sensor == 0x4){
		self->queueSouth++;
	}
	else if(sensor == 0x1){
		self->queueNorth++;
	}
	else if(sensor == (0x8 || 0x2)){
		carRun(self);
		LCDDR8 = 1;
	}
}

void changeDirection(Bridge *self){
	if((self->queueNorth == 0) && (self->queueSouth == 0)){
		ASYNC(self->outputs, transmit, 2);
	}else if (self->southLight){
		self->southLight = 0;
		AFTER(MSEC(5000), self, changeNorth, NULL);
		ASYNC(self->outputs, transmit, 0);
	}else if (self->northLight){
		self->northLight = 0;
		AFTER(MSEC(5000), self, changeSouth, NULL);
		ASYNC(self->outputs, transmit, 1);
	}
}

void carRun(Bridge *self){
	if((self->southLight == 1) && (self->queueSouth > 0)){			//left
		self->queueSouth--;
		self->carsOnBridge++;
		AFTER(MSEC(5000), self, carLeave, NULL);
		if((self->carspassed >= 5) && (self->queueNorth > 0)){ // 5 bilar + 5 sekunder(5 bilar till) blir 10 bilar
			self->carspassed = 0;
			changeDirection(self);
		}
	}else if((self->northLight == 1) && (self->queueNorth > 0)){	//right
		self->queueNorth--;
		self->carsOnBridge++;
		AFTER(MSEC(5000), self, carLeave, NULL);
		if((self->carspassed >= 5) && (self->queueSouth > 0)) { // 5 bilar + 5 sekunder(5 bilar till) blir 10 bilar
			self->carspassed = 0;
			changeDirection(self);
		}
	}
	updateDisp(self);
}

void carLeave(Bridge *self){
	if(self->carsOnBridge > 0){
		self->carsOnBridge--;
		self->carspassed++;
	}
}

void changeSouth(Bridge *self){
	self->southLight = 1;
}

void changeNorth(Bridge *self){
	self->northLight = 1;
}

void updateDisp(Bridge *self){
	ASYNC(self->gui, setleft, self->queueSouth);
	ASYNC(self->gui, setmiddle, self->carsOnBridge);
	ASYNC(self->gui, setright, self->queueNorth);
};