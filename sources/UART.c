/*
 * UART.c
 *
 * Created: 24/9/2021 08:42:09
 *  Author: ezema
 */ 

#include "../headers/UART.h"	

void UART_init(uint8_t ubrr){
	
	UBRR0 = ubrr;
	UCSR0B |= (1<<RXEN0) | (1<< TXEN0);
	UCSR0C |= (1<<UPM01) | (1<<UCSZ01) | (1<<UCSZ00);	//asincrono, bit de paridad y 8 bits de largo
	
}

void UART_Transmit( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)));
	/* Put data into buffer, sends the data */
	UDR0 = data;
}uint8_t UART_Receive()
{
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) );
	/* Get and return received data from buffer */
	return UDR0;
}void UART_Transmit_String(uint8_t *cadena){		while(*cadena){				UART_Transmit(*cadena);		cadena++; 				}}