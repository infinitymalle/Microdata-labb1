#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "Bridge.h"


void addcar(Bridge *self, int sensor){
	if(((self->northLight == 0) && (self->southLight == 0)) && ((self->queueNorth > 0) || (self->queueSouth > 0))){
		if(self->queueSouth > 0){
			self->southLight = 1;
		}else{
			self->northLight = 1;
		}
	}
	if (sensor == 0x4){
		self->queueSouth++;
	}
	else if(sensor == 0x1){
		self->queueNorth++;
	}
	updateDisp(self);
}

void changeDirection(Bridge *self){
	if((self->queueNorth == 0) && (self->queueSouth == 0)){
		ASYNC(self->outputs, transmit, 2);
	}else if (self->southLight){
		self->southLight = 0;
		AFTER(SEC(5), self, changeNorth, NULL);
		ASYNC(self->outputs, transmit, 0);
	}else if (self->northLight){
		self->northLight = 0;
		AFTER(SEC(5), self, changeSouth, NULL);
		ASYNC(self->outputs, transmit, 1);
	}
}

void carRun(Bridge *self){
	LCDDR8 = 1;
	if((self->southLight == 1) && (self->queueSouth > 0)){			//left
		self->queueSouth--;
		self->carsOnBridge++;
		AFTER(SEC(5), self, carLeave, NULL);
	}else if((self->northLight == 1) && (self->queueNorth > 0)){	//right
		self->queueNorth--;
		self->carsOnBridge++;
		AFTER(SEC(5), self, carLeave, NULL);

	}
	updateDisp(self);
}

void carLeave(Bridge *self){
	if((self->carsOnBridge > 0) && (self->carspassed <= 10)){
		self->carsOnBridge--;
		self->carspassed++;
	}
	if(self->carspassed >= 10) {		// 5 bilar + 5 sekunder(5 bilar till) blir 10 bilar
		self->carspassed = 0;
		changeDirection(self);
	}
	updateDisp(self);
}

void changeSouth(Bridge *self){
	self->southLight = 1;
	self->northLight = 0;
}

void changeNorth(Bridge *self){
	self->northLight = 1;
	self->southLight = 0;
}

void updateDisp(Bridge *self){
	ASYNC(self->gui, setleft, self->queueSouth);
	ASYNC(self->gui, setmiddle, self->carsOnBridge);
	ASYNC(self->gui, setright, self->queueNorth);
};