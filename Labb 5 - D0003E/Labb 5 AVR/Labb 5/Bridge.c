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
	if (self->northLight == 0 && self->southLight == 0 && self->queueNorth != 0){
		self->northLight = 1;
		ASYNC(self->outputs, transmit, 1);
	}
	else if(self->northLight == 0 && self->southLight == 0 && self->queueSouth != 0){
		self->southLight = 1;
		ASYNC(self->outputs, transmit, 0);
	}
	updateDisp(self);
}

void carRun(Bridge *self){
	updateDisp(self);
}

void carLeave(Bridge *self){
	updateDisp(self);
}

void changeDirection(Bridge *self){
	if(){
		
	}
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
//#include <avr/io.h>
//#include <avr/interrupt.h>
//#include <stdbool.h>
//#include "Bridge.h"
//
//
//void addcar(Bridge *self, int sensor){
	//
	//if (sensor == 0x4){
		//self->queueSouth++;
	//}
	//else if(sensor == 0x1){
		//self->queueNorth++;
	//}
	//if (self->northLight == 0 && self->southLight == 0 && self->queueNorth != 0){
		//self->northLight = 1;
		//ASYNC(self->outputs, transmit, 1);
	//}
	//else if(self->northLight == 0 && self->southLight == 0 && self->queueSouth != 0){
		//self->southLight = 1;
		//ASYNC(self->outputs, transmit, 0);
	//}
	//updateDisp(self);
//}
//
//void carRun(Bridge *self){
	//
	//if((self->southLight == 1) && (self->queueSouth > 0)){			//left
		//self->queueSouth--;
		//self->carsOnBridge++;
		//AFTER(SEC(5), self, carLeave, NULL);
	//}
	//if((self->northLight == 1) && (self->queueNorth > 0)){	//right
		//self->queueNorth--;
		//self->carsOnBridge++;
		//AFTER(SEC(5), self, carLeave, NULL);
	//}
	//updateDisp(self);
//}
//
//void carLeave(Bridge *self){
	//if((self->carsOnBridge > 0) && (self->carspassed < 7)){
		//self->carsOnBridge--;
		//self->carspassed++;
	//}
	//if((self->southLight == 1 && self->queueSouth == 0 && self->queueNorth > 0) || (self->northLight == 1 && self->queueNorth == 0 && self->queueSouth > 0)){
		//changeDirection(self);
	//}
	//if(self->carspassed >= 10) {		// 5 bilar + 5 sekunder(5 bilar till) blir 10 bilar
		//self->carspassed = 0;
		//self->northLight = 0;
		//self->southLight = 0;
		//ASYNC(self->outputs, transmit, 2);
		//changeDirection(self);
	//}
	//if(self->queueNorth == 0 && self->queueSouth == 0){
		//changeDirection(self);
	//}
	//updateDisp(self);
//}
//
//void changeDirection(Bridge *self){
//// 	if(self->carsOnBridge > 0){
//// 		AFTER(SEC(self->carsOnBridge), self, changeDirection, NULL);
//// 		ASYNC(self->outputs, transmit, 2);
	//if (self->northLight == 1){
		//self->northLight = 0;
		//self->southLight = 1;
		////AFTER(SEC(5), self, changeSouth, NULL);
		//ASYNC(self->outputs, transmit, 0);
	//}
	//else if (self->southLight == 1){
		//self->southLight = 0;
		//self->northLight = 1;
		////AFTER(SEC(5), self, changeNorth, NULL);
		//ASYNC(self->outputs, transmit, 1);
	//}
//// 	if(self->queueNorth == 0 && self->queueSouth == 0){
//// 		self->northLight = 0;
//// 		self->southLight = 0;
//// 		ASYNC(self->outputs, transmit, 2);
//// 	}
//}
//
//// void changeSouth(Bridge *self){
//// 	self->southLight = 1;
//// 	//ASYNC(self->outputs, transmit, );
//// }
//// 
//// void changeNorth(Bridge *self){
//// 	self->northLight = 1;
//// }
//
//void updateDisp(Bridge *self){
	//ASYNC(self->gui, setleft, self->queueSouth);
	//ASYNC(self->gui, setmiddle, self->carsOnBridge);
	//ASYNC(self->gui, setright, self->queueNorth);
//}