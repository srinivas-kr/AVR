/*
 * GccApplication1.c
 *
 * Created: 17-07-2014 PM 11:45:23
 *  Author: srinivas
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#define F_CPU 16000000UL
#include "UART_2560.h" 
#define BAUDRATE 9600

#define BAUD_PRESCALLER (((F_CPU / (BAUDRATE * 16UL))) - 1)
//////////////////////////////////////
#define UART_RX_BUFFER_MASK ( UART_RX_BUFFER_SIZE - 1)
#define UART_TX_BUFFER_MASK ( UART_TX_BUFFER_SIZE - 1)
/////////////////////////////////
#define ATMEGA_USART0
#define ATMEGA_USART1
#define UART0_RECEIVE_INTERRUPT   USART0_RX_vect
#define UART1_RECEIVE_INTERRUPT   USART1_RX_vect
#define UART0_TRANSMIT_INTERRUPT  USART0_UDRE_vect
#define UART1_TRANSMIT_INTERRUPT  USART1_UDRE_vect
#define UART0_STATUS   UCSR0A
#define UART0_CONTROL  UCSR0B
#define UART0_DATA     UDR0
#define UART0_UDRIE    UDRIE0
#define UART1_STATUS   UCSR1A
#define UART1_CONTROL  UCSR1B
#define UART1_DATA     UDR1
#define UART1_UDRIE    UDRIE1
///////////////////////////////////////
static volatile unsigned char UART_TxBuf[UART_TX_BUFFER_SIZE];
static volatile unsigned char UART_RxBuf[UART_RX_BUFFER_SIZE];
static volatile unsigned char UART_TxHead;
static volatile unsigned char UART_TxTail;
static volatile unsigned char UART_RxHead;
static volatile unsigned char UART_RxTail;
static volatile unsigned char UART_LastRxError;

ISR (UART0_RECEIVE_INTERRUPT)
{
	unsigned char tmphead;
	unsigned char data;
	unsigned char usr;
	unsigned char lastRxError;
	
	
	/* read UART status register and UART data register */
	usr  = UART0_STATUS;
	data = UART0_DATA;
	
	/* */

	#if defined( ATMEGA_USART0 )
	lastRxError = (usr & (_BV(FE0)|_BV(DOR0)) );
	#endif
	
	/* calculate buffer index */
	tmphead = ( UART_RxHead + 1) & UART_RX_BUFFER_MASK;
	
	if ( tmphead == UART_RxTail ) {
		/* error: receive buffer overflow */
		lastRxError = UART_BUFFER_OVERFLOW >> 8;
		}else{
		/* store new index */
		UART_RxHead = tmphead;
		/* store received data in buffer */
		UART_RxBuf[tmphead] = data;
	}
	UART_LastRxError |= lastRxError;
}

ISR (UART0_TRANSMIT_INTERRUPT)
{
	unsigned char tmptail;

	
	if ( UART_TxHead != UART_TxTail) {
		/* calculate and store new buffer index */
		tmptail = (UART_TxTail + 1) & UART_TX_BUFFER_MASK;
		UART_TxTail = tmptail;
		/* get one byte from buffer and write it to UART */
		UART0_DATA = UART_TxBuf[tmptail];  /* start transmission */
		}else{
		/* tx buffer empty, disable UDRE interrupt */
		UART0_CONTROL &= ~_BV(UART0_UDRIE);
	}
}



//int main(void)
//{
	////char c;
	//USART_init();        //Call the USART initialization code
	//_delay_ms(10);
	//USART1_init();
	//
	//sei();
	//USART_send('s');
	//while(1){      
				////c=USART3_receive();
				////USART3_send(c);
				////USART_send('s');
				////_delay_ms(200);
	//
		//USART_puts("got it");
		//_delay_ms(3000);        
		//
	//}
	//
	//return 0;
//}

///////////////////USART0//////////////////////////////////////////////

void USART_begin(void){
	
	UBRR0H = (uint8_t)(BAUD_PRESCALLER>>8);
	UBRR0L = (uint8_t)(BAUD_PRESCALLER);
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	UCSR0C = (3<<UCSZ00);
}



unsigned char USART_receive(void){
	
	while(!(UCSR0A & (1<<RXC0)));
	return UDR0;
	
}

void USART_printc(unsigned char data){
	
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;
	
}

void USART_print(char *str)
{	
	while(*str )
	{
		USART_printc(*str++);
	}
	
}

void USART_println(char *str)
{
	while(*str )
	{
		USART_printc(*str++);
	}
	USART_printc('\r');
	USART_printc('\n');
	
}

//////////////////USART1////////////////////////////////////////
void USART1_begin(void){                           //USART1 initialisation 
	
	UBRR1H = (uint8_t)(BAUD_PRESCALLER>>8);
	UBRR1L = (uint8_t)(BAUD_PRESCALLER);
	UCSR1B = (1<<RXEN1)|(1<<TXEN1);
	UCSR1C = (3<<UCSZ10);
}

void USART1_printc( unsigned char data){            //USART1 send
	
	while(!(UCSR1A & (1<<UDRE1)));
	UDR1 = data;
	
}

unsigned char USART1_receive(void){
	
	while(!(UCSR1A & (1<<RXC1)));
	return UDR1;
	
}

void USART1_print(char *str)
{
	while(*str )
	{
		USART1_printc(*str++);
	}
	
}

void USART1_println(char *str)
{
	while(*str )
	{
		USART1_printc(*str++);
	}
	USART1_printc('\r');
	USART1_printc('\n');
	
}
//////////////////////////////////////////////USART2//////////////////////////

void USART2_begin(void){                           //USART1 initialisation
	
	UBRR2H = (uint8_t)(BAUD_PRESCALLER>>8);
	UBRR2L = (uint8_t)(BAUD_PRESCALLER);
	UCSR2B = (1<<RXEN2)|(1<<TXEN2);
	UCSR2C = (3<<UCSZ20);
}

void USART2_printc( unsigned char data){            //USART1 send
	
	while(!(UCSR2A & (1<<UDRE2)));
	UDR2 = data;
	
}

unsigned char USART2_receive(void){
	
	while(!(UCSR2A & (1<<RXC2)));
	return UDR2;
	
}

void USART2_print(char *str)
{
	while(*str )
	{
		USART2_printc(*str++);
	}
	
}

void USART2_println(char *str)
{
	while(*str )
	{
		USART2_printc(*str++);
	}
	USART2_printc('\r');
	USART2_printc('\n');
	
}
///////////////////////////USART3/////////////////////////////////////

void USART3_begin(void){                           //USART1 initialisation
	
	UBRR3H = (uint8_t)(BAUD_PRESCALLER>>8);
	UBRR3L = (uint8_t)(BAUD_PRESCALLER);
	UCSR3B = (1<<RXEN3)|(1<<TXEN3);
	UCSR3C = (3<<UCSZ30);
}

void USART3_printc( unsigned char data){            //USART1 send
	
	while(!(UCSR3A & (1<<UDRE3)));
	UDR3 = data;
	
}

unsigned char USART3_receive(void){
	
	while(!(UCSR3A & (1<<RXC3)));
	return UDR3;
	
}


void USART3_print(char *str)
{
	while(*str )
	{
		USART3_printc(*str++);
	}
	
}

void USART3_println(char *str)
{
	while(*str )
	{
		USART3_printc(*str++);
	}
	USART3_printc('\r');
	USART3_printc('\n');
	
}



void USART_flush()
{
	char m;
    while(!(UCSR0A & (1<<RXC0)));
    m= UDR0;
}




/////////////////////////////////////////////////////////////////////////////////////////
void recvcommand(char *response)
{
	for(;;)
	{
	  unsigned int c;
	  c = USART_receive();
	  if ( c & UART_NO_DATA )
	   { }
	  else
	   {
		 while(USART_receive() != '\n' );		 
	     while( ((c = USART_receive()) != '\r') || (( c = USART_receive()) != '\n') )
		 if(c != '^')
			 *response++ = c;
		 else
		  break;
	   }
	 }
}


void recvResponse( void)
{
	  unsigned int c;
	 c = USART1_receive();
        if ( c & UART_NO_DATA )
        {
          
        }
        else
        {
            
            if ( c & UART_FRAME_ERROR )
            {
               
               USART_print("UART Frame Error: ");
            }
            if ( c & UART_OVERRUN_ERROR )
            {
               
                USART_print("UART Overrun Error: ");
            }
            if ( c & UART_BUFFER_OVERFLOW )
            {
                USART_print("Buffer overflow error: ");
            }
            
		     while(USART1_receive() != '\n' );
		 
		     while( ((c = USART1_receive()) != '\r') || (( c = USART1_receive()) != '\n') ) 
			USART_printc(c);
			
        }
		USART_printc('\n');
}