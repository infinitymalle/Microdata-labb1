#ifndef _GUI_h
#define _GUI_h

#include <stdbool.h>

void LCD_Init();
void printAt(long num, int pos);
void writeChar(char ch, int pos);

#endif