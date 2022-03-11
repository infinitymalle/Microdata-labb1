/*
 * Labb 5.c
 *
 * Created: 2022-03-10 09:54:03
 * Author : Malkolm Lundkvist & Eddie Höglund
 */ 

#include <avr/io.h>


int main(void){
	//void LCD_Init(void)
	
	USART_Init();
	
	INSTALL();
	
	TINYTIMBER();
}

