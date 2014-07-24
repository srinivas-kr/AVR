#define F_CPU 16000000UL
#include "UART_2560.h"
#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>

char *buffer=" ";

void rcv_command(char *response)
{
	char c;
	while (1)
	{
		c=USART_receive();
		if( c & UART_NO_DATA)
		{
			USART_println("No data received");
		}
		else
		{
			*response++ = c;
			while((c=USART_receive()) != '^')
			*response++ = c;
			break;
		}
	}
}


int main(void)
{
	USART_begin();        //Call the USART initialization code
	_delay_ms(10);
	USART1_begin();
	
	sei();
	
	USART_println("Type AT command end with ^: ");
	
	while(1)
	{
		rcv_command(buffer);
	    USART1_println(buffer);
		 *buffer= 0;
	    recvResponse();
	}
		
	return 0;
}