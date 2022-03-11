#ifndef GUI_H_
#define GUI_H_

#include <avr/io.h>
//#include "Pinwriter.h"

#define initGUI() {initObject()}

typedef struct {
	Object super;
	
} GUI;

void LCD_Init(void);
void printAt(long num, int pos);
void writeChar(char ch, int pos);
void updatedisplay(GUI *self);


#endif