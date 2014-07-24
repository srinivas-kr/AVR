////////*****USART 2560*****///////////
/*
 Asynchronus mode
 start bit 0
 stop bit  1
 bits      8
 parity   NONE
 BAUDRATE 9600;
 F_CPU 16000000;
 UASRT0, USART1, USART2, USART3; // tested with gl868 modem
 c file- UART_2560.C
 h file- UART_2560.h

////UART0//functions////
// USART0 initialise with respective baud rate we mention  
void USART_begin(void);

//receive the character from Rx0
unsigned char USART_receive(void);

//send charcter through TX0
void USART_printc( unsigned char data);

//send string through Tx0
Void USART_print(  char *str);

//send string through Tx0 with new line
void USART_println( char *str);

////UART1//functions////
// USART1 initialise with respective baud rate we mention  
void USART1_begin(void);

//receive the character from Rx1
unsigned char USART1_receive(void);

//send charcter through TX1
void USART1_printc( unsigned char data);

//send string through Tx1
Void USART1_print(  char *str);

//send string through Tx1 with new line
void USART1_println( char *str);

////UART2//functions////
// USART2 initialise with respective baud rate we mention  
void USART2_begin(void);

//receive the character from Rx2
unsigned char USART2_receive(void);

//send charcter through TX2
void USART2_printc( unsigned char data);

//send string through Tx2
Void USART2_print(  char *str);

//send string through Tx2 with new line
void USART2_println( char *str);


////UART3//functions////
// USART3 initialise with respective baud rate we mention  
void USART3_begin(void);

//receive the character from Rx3
unsigned char USART3_receive(void);

//send charcter through TX3
void USART3_printc( unsigned char data);

//send string through Tx3
Void USART3_print(  char *str);

//send string through Tx3 with new line
void USART3_println( char *str);