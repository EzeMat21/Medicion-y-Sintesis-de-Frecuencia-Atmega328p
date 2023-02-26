/*
 * Proyecto_Modulo3.c
 *
 * Created: 22/11/2022 14:01:52
 * Author : ezema
 */ 


//Sintesis de un frecuencímetro

//-------------------------------------------------------------- DEFINES Y MACROS ------------------------------------------------------------------------------------//

#define F_CPU 16000000UL
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

#define Si_valor_es_par(valor) (valor==0)|(valor==2)|(valor==4)|(valor==6)|(valor==8)
#define Si_valor_es_impar(valor) (valor==1)|(valor==3)|(valor==5)|(valor==7)

//--------------------------------------------------------------- INCLUDES -------------------------------------------------------------------------------------------//

#include <avr/interrupt.h>
#include <util/delay.h>

#include "C:\Users\ezema\OneDrive\Documentos\Atmel Studio\7.0\Proyecto_Modulo3\Proyecto_Modulo3\headers\medicion.h"
#include "C:\Users\ezema\OneDrive\Documentos\Atmel Studio\7.0\Proyecto_Modulo3\Proyecto_Modulo3\headers\sintesis.h"
#include "C:\Users\ezema\OneDrive\Documentos\Atmel Studio\7.0\Proyecto_Modulo3\Proyecto_Modulo3\headers\boton.h"

//------------------------------------------------------------ VARIABLES GLOBALES ------------------------------------------------------------------------------------//

volatile uint32_t conteo=0;
volatile uint8_t estado = 0;
volatile uint8_t valor = 0;
volatile uint8_t indice = 0;

uint8_t cadena1[] = "MODO MEDICION - ";
uint8_t cadena2[] = "MODO SINTESIS\r";


//Estos valores hay que dividirlos por 100 para obtener el valor de voltaje real. Seno de amplitud 2.5 con valor medio 2.5 (de 0 a 5V).	

const uint16_t seno[] =	{250,	266,	281,	297,	312,	327,	342,	356,	370,	384,	397,	409,	421,	432,	443,	452,	461,
						469,	476,	482,	488,	492,	496,	498,	500,	500,	500,	498,	496,	492,	488,	482,	476,	469,
						461,	452,	443,	432,	421,	409,	397,	384,	370,	356,	342,	327,	312,	297,	281,	266,	250,
						234,	219,	203,	188,	173,	158,	144,	130,	116,	103,	91,		79,		68,		57,		48,		39,		31,
						24,		18,		12,		8,		4,		2,		0,		0,		0,		2,		4,		8,		12,		18,		24,		31,		39,
						48,		57,		68,		79,		91,		103,	116,	130,	144,	158,	173,	188,	203,	219,	234};


//--------------------------------------------------------------------  MAIN -----------------------------------------------------------------------------------------//


uint8_t frecuencia;

int main(void)
{
	cli();
	ADC_init();					//Inicializo el conversor
	UART_init(MYUBRR);			//Inicializo el puerto serie UART
	INT0_init();
	sei();						//Habilito las interrupciones globales
	
	_delay_ms(10);				//Espero a que se inicialicen 
	
	
    while (1) 
    {	
		
		if(estado == 1){	//Luego de realizar el conteo de los cruces por cero (en realidad los cruces por 2.5V), deshabilito las interrupciones por ADC.
			
			Deshabilitar_ADC();
			UART_Transmit_String(cadena1);
			frecuencia = Imprimir_medicion(conteo);
			_delay_ms(10);
			
			estado = 2;		
		}
		
		
		if(estado == 2){	//Standby, No se hace nada
			
		}
		
		if(estado == 3){		//Comienza la sintesis del seno
			
			UART_Transmit_String(cadena2);
			PWM_init();
			Timer0_init(frecuencia);	
			
			_delay_ms(10);		//Espero a que se inicialicen
			
			estado = 4;

		}
		
		if(estado == 4){	//Standby, No se hace nada
					
		}
		
		if(estado == 5){
			
			cli();
			Deshabilitar_Timer0();
			Deshabilitar_PWM();		
			Habilitar_ADC();
			sei();
			
			_delay_ms(10);	//Espero a que se inicialice
	
			estado = 0;		//Se reinician las variables para comenzar una nueva medición
			conteo = 0;
			valor = 0;
		}
		

    }
}

//----------------------------------------------------------------- INTERRUPCIONES -----------------------------------------------------------------------------------//

//Rutina de interrupcion (Corresponde a la medición de frecuencia - "estado 0")
ISR(ADC_vect){
	
	uint16_t adc_value1 = ADCW;
	
	if( (adc_value1 >= 768) && Si_valor_es_par(valor) ){			//Voy contando los máximos de amplitud de la señal para un tiempo de 4 periodos (5 máximos)
		
		valor++;
	}
	if( (adc_value1 <= 256) &&  Si_valor_es_impar(valor) ){			//Voy contando los mínimos de amplitud de la señal para un tiempo de 4 periodos (4 mínimos)

		valor++;
	}
	
	if( valor == 9){		//Cuando termino de contar las amplitudes para 4 periodos, habilito el flag para entrar al main y deshabilitar esta rutina de interrupcion.
		estado = 1;
		conteo--;
	}

		conteo++;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------//

//Interrupcion por comparación Timer 0
ISR(TIMER0_COMPA_vect){
	
	uint8_t i = indice;
	
	indice = Sintetizar_frecuencia(i, seno[i]);
	
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//Interrupción por INT0 (Pulsador)

ISR(INT0_vect){
	
	if(estado == 2){
		estado = 3;
	}
	
	if(estado == 4){
		estado = 5;
	}
		
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------//
