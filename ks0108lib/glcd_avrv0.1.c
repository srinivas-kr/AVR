/*
 * glcd_avrv0.c
 *
 * Created: 22-07-2014 PM 01:28:35
 *  Author: srinivas
 */ 

#define F_CPU 1000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>
#include "KS0108.h"
#include "KS0108_AVR.h"
#include "graphic.h"

float temp = 33.00;
char buff[10];

int main(void)
{
	 GLCD_Initalize();
	 GLCD_ClearScreen();
	 GLCD_GoTo(4,0);
	 GLCD_WriteString("yuktix Technologies");
	 GLCD_Line(2,11,116,11);
    while(1)
    { 
		GLCD_GoTo(4,2);
		GLCD_WriteString("Temp:");
		GLCD_GoTo(33,2);
		GLCD_WriteString("34.00'C");
	////////////////////////////////////
		GLCD_GoTo(4,3);
		GLCD_WriteString("Hum :");
		GLCD_GoTo(33,3);
		GLCD_WriteString("83.32 %");
	////////////////////////////////////
		GLCD_GoTo(4,4);
		GLCD_WriteString("Wet :");
		GLCD_GoTo(33,4);
		GLCD_WriteString("00.00 ");
	///////////////////////////////////
		GLCD_GoTo(4,5);
		GLCD_WriteString("Mois: ");
		GLCD_GoTo(33,5);
		GLCD_WriteString("38.82 %");
    ////////////////////////////////////
	   	GLCD_GoTo(4,6);
	   	GLCD_WriteString("Hum2: ");
	   	GLCD_GoTo(33,6);
	   	GLCD_WriteString("78.12 %");
	////////////////////////////////////
	  GLCD_GoTo(4,7);
	  GLCD_WriteString("wet2: ");
	  GLCD_GoTo(33,7);
	  GLCD_WriteString("01.00 ");
	  ////////////////////////////////////
    }
}

