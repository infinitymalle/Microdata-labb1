#ifndef _GUI_h
#define _GUI_h

#include <stdbool.h>
#include "TinyTimber.h"

#define initGUI() {initObject()}

typedef struct {
	Object super;
} GUI;

void LCD_Init();
void printAt(long num, int pos);
void writeChar(char ch, int pos);

#endif _GUI_h