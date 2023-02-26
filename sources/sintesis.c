/*
 * sintesis.c
 *
 * Created: 20/12/2022 22:26:27
 *  Author: ezema
 */ 


//Tendria que tener en cuenta la cantidad de bits con la que se representa el PWM y sabiendo la frecuencia del PWM puedo obtener la cantidad de puntos que puedo graficar
//para la máxima frecuencia que es f=200Hz. Num de puntos = Tseñal / Tmuestreo = fmuestreo / fseñal.
//Se utilizará el timer 0 para que cada ~5us se ejecute una rutina de interrupcion y se actualice el valor de la señal PWM, de forma de generar un nuevo valor cada 5us.
//Variando los registros del timer modifico cada cuanto tiempo se va a ejecutar la interrupcion y por tanto la frecuencia de la señal a sintetizar.

#include "../headers/sintesis.h"

//Inicializo el Timer 0 para modo CTC
void Timer0_init(uint8_t frecuencia){	//Este va a ejecutar la rutina de interrupcion para que los puntos de voltaje del seno sean equiespaciados y en ella se ejecuta la salida del PWM
	
	TCCR0A |= (1<<WGM01);		//CTC Mode
	TCCR0B |= (1<<CS02);		//Prescalor de 256
	
	//Como queremos sintetizar 100 puntos por periodo del seno a la salida, la frec del timer debe ser 100 veces la frec del seno a sintetizar.

	OCR0A = (F_CPU/PRESCALER_TIMER0/frecuencia/100);
	
	TIMSK0 |= (1<<OCIE0A);		//Habilito la interrupcion por comparación
	
}


//FAST PWM Mode
//frecPWM =	fclock/(N*256), N es el prescaler

void PWM_init(){
	
	DDRB |= (1<<DDB3);	//Salida el pin OC2A
	
	TCCR2A |= (1<<COM2A1);				//Clear OC2A on compare match, set OC2A at BOTTOM, (non-inverting mode)
	TCCR2A |= (1<<WGM21)|(1<<WGM20);	//Fast PWM
	 
	TCCR2B |= (1<<CS20);				//No prescaling, N=1; fPWM = 62.5kHz
	
}

uint8_t Sintetizar_frecuencia(uint8_t indice, uint16_t valor){
	
	uint16_t x = ((valor/10)*255)/50;
	
	OCR2A = x;
	indice++;
	if(indice == 100){
		indice=0;
	}
	
	return indice;
}


void Deshabilitar_PWM(){		//Frenar el Timer 2
	
	TCCR2B &= ~(1<<CS22);
	TCCR2B &= ~(1<<CS21);
	TCCR2B &= ~(1<<CS20);
}

void Deshabilitar_Timer0(){		//Frenar el Timer 0
	
	TCCR0B &= ~(1<<CS02);
	TCCR0B &= ~(1<<CS01);
	TCCR0B &= ~(1<<CS00);
	
	TIMSK0 &= ~(1<<OCIE0A);		//Deshabilito la interrupcion por comparación
}









