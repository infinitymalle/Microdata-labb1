#ifndef _GUI_h
#define _GUI_h

#include "TinyTimber.h"
//#include "PulseGenerator.h"

#define initGUI() {initObject()};

typedef struct {
	Object super;
} GUI;

void LCD_Init();
void printAt(long num, int pos);
void writeChar(char ch, int pos);
//void currentFrequency(GUI *self);
void updatedisplay(int pos);
#endif