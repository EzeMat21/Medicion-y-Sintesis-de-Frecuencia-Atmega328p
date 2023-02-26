/*
 * sintesis.h
 *
 * Created: 20/12/2022 22:26:35
 *  Author: ezema
 */ 

#define PRESCALER_TIMER0 256

#define F_CPU 16000000UL

#include <avr/io.h>

#ifndef SINTESIS_H_
#define SINTESIS_H_

void Timer0_init(uint8_t frecuencia);
void PWM_init();
uint8_t Sintetizar_frecuencia(uint8_t indice, uint16_t valor);
void Deshabilitar_PWM();
void Deshabilitar_Timer0();


#endif /* SINTESIS_H_ */