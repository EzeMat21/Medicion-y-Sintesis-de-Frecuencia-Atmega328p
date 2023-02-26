/*
 * medicion.h
 *
 * Created: 20/12/2022 22:25:17
 *  Author: ezema
 */ 

#define periodo_ADC 100 //En microsegundos.
#define N 4				//Numero de periodos que se van a medir

#include <avr/io.h>
#include "..\headers\UART.h"

#ifndef MEDICION_H_
#define MEDICION_H_


void ADC_init();
uint8_t Imprimir_medicion(uint32_t conteo);
void Deshabilitar_ADC();
void Habilitar_ADC();

#endif /* MEDICION_H_ */