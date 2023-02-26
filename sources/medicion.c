/*
 * medicion.c
 *
 * Created: 19/12/2022 20:42:16
 *  Author: ezema
 */ 

#include "../headers/medicion.h"

//Inicializo el ADC

void ADC_init(){
	
	
	ADMUX = 0x00;
	ADMUX |= (1<<REFS0);		//Configuro la tensión de referencia a AVCC y utilizo el canal 0 como pin de conversion (ADC0)
	
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);					//Configuro el prescaler para que el ADC trabaje a 1MHz
	ADCSRB = 0x00;										//Configuración Free Running Mode (conversiones consecutivas)
	
	ADCSRA |= (1<<ADATE);               //Signal source, in this case is the free-running
	ADCSRA |= (1<<ADEN);                //Habilito el ADC
	
	ADCSRA |= (1<<ADIE);				//Habilito la interrupcion
	ADCSRA |= (1<<ADSC);				// Start conversion
	
}


//Yo se que lo que tarda el ADC en convertir la señal a digital son 13 ciclos, como manejamos una freq_ADC=125khz, entonces T_adc = 13*(1/125kHz)= 104us.
//El periodo del ADC se lo ha escrito como 'periodo_ADC' y 'conteo' es la cantidad total de periodos T_adc contados en un determinado lapso.
//Si por ejemplo observamos N periodos de la señal a medir (contando la cantidad de veces que cruza por cero o por 2.5v en este caso) obtenemos que el
//periodo de la señal a medir es T = (conteo*T_adc)/N. Si tomamos la inversa para obtener la freq entonces nos queda: freq = N/(conteo*T_adc). 
//Si escribimos T_adc = 104us = 104/10e6, obtenemos la expresion de abajo:  freq = (N*10e6)/(conteo*periodo_ADC).

uint8_t Imprimir_medicion(uint32_t conteo){
	
	uint16_t frec_medida;
	
	uint8_t mensaje[] = "Frecuencia medida: ";
	uint8_t punto[] = ".";
	uint8_t mensaje2[] = "Hz\r";
	
	uint8_t buffer[6];
	uint8_t buffer1[6];
	
	frec_medida = (N*10*1e6)/periodo_ADC/conteo;			//Obtengo la frecuencia multiplicada por 10
	
	uint8_t *a = itoa(frec_medida/10, buffer,10);		//Aqui divido por 10 y lo convierto a caracter. Lo que obtengo es la parte entera.
	uint8_t *b = itoa(frec_medida % 10, buffer1,10);	//Aquí obtengo el resto de dividirlo por 10. Obtengo la parte despues de la coma.
	
	
	UART_Transmit_String(mensaje);
	UART_Transmit_String(a);
	UART_Transmit_String(punto);
	UART_Transmit_String(b);
	UART_Transmit_String(mensaje2);
	
	frec_medida = frec_medida/10;
	return frec_medida;
	
}

void Deshabilitar_ADC(){
	
	ADCSRA &= ~(1<<ADIE);		//Deshabilito la interrupcion
	ADCSRA &= ~(1<<ADEN);		//Deshabilito el conversor
}

void Habilitar_ADC(){
	
	ADCSRA |= (1<<ADIE);				//Habilito la interrupcion
	ADCSRA |= (1<<ADEN);                //Habilito el ADC
	ADCSRA |= (1<<ADSC);				// Start conversion
	
}