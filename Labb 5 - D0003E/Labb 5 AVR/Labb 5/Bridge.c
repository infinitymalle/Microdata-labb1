#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "Bridge.h"

#define northArrive 0x1 // North car arrive
#define southArrive 0x4 // South car arrive

void addcar(Bridge *self, int sensor){
	
	if (sensor == southArrive){
		self->queueSouth++;
	}
	else if(sensor == northArrive){
		self->queueNorth++;
	}
	if(self->firstcar == 1 && self->queueNorth > 0){
		setNorth(self);
		self->firstcar = 0;
	}else if(self->firstcar == 2 && self->queueSouth > 0){
		setSouth(self);
		self->firstcar = 0;
	}
		
	if ((self->carsOnBridge == 0) && (self->northLight == 0) && (self->southLight == 0)){
		if (self->queueNorth > 0){
			setNorth(self);
			self->firstcar = 1;
		}
		else if(self->queueSouth > 0){
			setSouth(self);
			self->firstcar = 2;
		}
	}
	updateDisp(self);
}

void carRun(Bridge *self){

	if(self->southLight == 1){
		self->carsOnBridge++;
		self->queueSouth--;
		self->carspassed++;
		AFTER(SEC(5), self, carLeave, NULL);
		if(((self->queueSouth <= 0) && (self->queueNorth > 0)) || (self->carspassed >= 5)){
			stop(self);
			self->carspassed = 0;
			AFTER(SEC(5), self, setNorth, NULL);
		}
	}
	else if(self->northLight == 1){
		self->carsOnBridge++;
		self->queueNorth--;
		self->carspassed++;
		AFTER(SEC(5), self, carLeave, NULL);
		if(((self->queueNorth <= 0) && (self->queueSouth > 0)) || (self->carspassed >= 5)){
			stop(self);
			self->carspassed = 0;
			AFTER(SEC(5), self, setSouth, NULL);
		}
	}
	if((self->queueNorth <= 0) && (self->queueSouth <= 0)){
		stop(self);
	}
	if((self->queueNorth <= 0) && (self->southLight == 1)){
		self->carspassed = 0;
	}else if((self->queueSouth <= 0) && (self->northLight == 1)){
		self->carspassed = 0;
	}

	updateDisp(self);
}

void carLeave(Bridge *self){
	self->carsOnBridge--;
	updateDisp(self);
}

void setNorth(Bridge *self){
	self->northLight = 1;
	self->southLight = 0;
	ASYNC(self->outputs, transmit, 1);
}

void setSouth(Bridge *self){
	self->northLight = 0;
	self->southLight = 1;
	ASYNC(self->outputs, transmit, 0);
}

void stop(Bridge *self){
	self->northLight = 0;
	self->southLight = 0;
	ASYNC(self->outputs, transmit, 2);
}

void updateDisp(Bridge *self){
	ASYNC(self->gui, setleft, self->queueSouth);
	ASYNC(self->gui, setmiddle, self->carsOnBridge);
	ASYNC(self->gui, setright, self->queueNorth);
}
