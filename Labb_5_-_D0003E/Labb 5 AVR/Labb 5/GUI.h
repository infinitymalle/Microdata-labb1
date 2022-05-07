#ifndef GUI_H_
#define GUI_H_

#include <avr/io.h>
#include "TinyTimber.h"

#define initGUI() {initObject()}

typedef struct {
	Object super;
	//int leftDisp;
	//int middleDisp;
	//int rightDisp;
} GUI;

void general_Init(void);
void USART_Init();
void printAt(long num, int pos);
void writeChar(char ch, int pos);
void updatedisplay(GUI *self);
void setleft(GUI *self, int val);
void setmiddle(GUI *self, int val);
void setright(GUI *self, int val);

#endif