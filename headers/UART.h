/*
 * UART.h
 *
 * Created: 24/9/2021 09:31:48
 *  Author: ezema
 */ 

#include <avr/io.h>

#ifndef UART_H_
#define UART_H_

void UART_init(uint8_t baud);
void UART_Transmit( unsigned char data );
uint8_t UART_Receive();
void UART_Transmit_String(uint8_t *cadena);

#endif /* UART_H_ */